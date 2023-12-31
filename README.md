# c/cpp

## 类型转换

- 在大多数`表达式`中，类型小的首先提升为较大的类型。
- 在`条件语句`中，**非布尔值转换**成**布尔**类型。 0转为false， 非0(包括负数)转为True
- `初始化过程`中， 初始值转换成变量的类型
- 在`赋值语句`中，**右侧**运算对象**转换成左侧**运算对象的类型。（和初始化类似）
- 如果`算术运算或关系运算`的运算对象有**多种类型**，需要**转换成同一种类型**。
- `函数调用`时也会发生类型转换。

### 算术转换

- 运算符的运算对象将转换成最宽的类型
- 有符号的转成无符号的
- 低位转成高位的

## Const

### 作用

1. 修饰变量，放在关键词的左右含义一样，但是一般放在左侧，表示该变量不可变;

   ```c++
       const int a = 1;
       int const b = 2;
   
       //a = 2;  error
       //b = 3;  error
   ```

2. 修饰指针，分为指向常量的指针(pointer to const) 和 自身是常量的指针(const pointer);

   > 区分这两者，可以看const是在*的左边还是右边。如果在左边，那么就是修饰指针指向的值，在右边，则是修饰指针自身。

   ```c++
       int c = 3, d = 4;
       
       const int *p1 = &c;       //pointer to const，      常量指针
       int *const p2 = &d;       //const pointer，         指针常量
       const int *const p3 = &c; //const pointer to const
   	//    *p1 = 3;  error
   	//    p2 = &a;  error
   	//    p3 = &b;  error
   	//    *p3 = 4;  error
   ```

3. 修饰引用，指向常量的引用(reference to const) , 既可以避免拷贝，又避免了对引用值的修改；没有 const reference，因为引用只是对象的别名，引用不是对象，不能用 const 修饰, 并且引用不能更改其所指向的对象(类似指针常量)；如果const修饰了引用，那么既不能修改指向对象，也不能修改引用值。

   ```c++
       int e = 5, f = 6;
   
       const int &ee = e;
       //ee = 6; error
       //ee = f; error
   ```

4. 修饰成员函数，说明该成员函数内不能修改成员变量。需要在定义时放在函数名后。

   > 注意，常量对象只能调用常量成员函数；正常对象既可以调用常量成员函数，也可以调用非常量成员函数

   ```c++
       int get() const; //
   ```

   ### 宏定义#define和const常量

   | 宏定义               | const常量      |
   | -------------------- | -------------- |
   | 相当于字符替换       | 常量声明       |
   | 预处理器处理         | 编译器处理     |
   | 无类型安全检查       | 有类型安全检查 |
   | 不分配内存           | 要分配内存     |
   | 存储在代码段         | 存储在数据段   |
   | 可通过 `#undef` 取消 | 不可取消       |
   
   
   
## C程序编译后的程序空间

   1. 栈（stack）：由编译器进行管理，自动分配和释放，存放函数调用过程中的各种参数、局部变量、返回值以及函数返回地址。操作方式类似数据结构中的栈。
   2. 堆（heap）：用于程序动态申请分配和释放空间。C语言中的malloc和free，C++中的new和delete均是在堆中进行的。正常情况下，程序员申请的空间在使用结束后应该释放，若程序员没有释放空间，则程序结束时系统自动回收。注意：这里的“堆”并不是数据结构中的“堆”。
   3. 全局（静态）存储区：分为DATA段和BSS段。DATA段（全局初始化区）存放初始化的全局变量和静态变量；BSS段（全局未初始化区）存放未初始化的全局变量和静态变量。程序运行结束时自动释放。其中BBS段在程序执行之前会被系统自动清0，所以未初始化的全局变量和静态变量在程序执行之前已经为0。
   4. 文字常量区：存放常量字符串。程序结束后由系统释放。
   5. 程序代码区：存放程序的二进制代码。

   

## 局部变量，全局变量 [code](./code/global_local/global_local.cpp)

| 局部变量                                       | 全局变量                                                 |
| ---------------------------------------------- | -------------------------------------------------------- |
| 定义在一个代码块内部，在代码块之外是不可访问的 | 定义在所有函数之外，并且在其作用域内的所有函数都可以访问 |
| 生存周期是定义该变量的函数执行周期             | 生存周期是程序从变量定义到整个程序结束                   |
| 存放于栈中，由操作系统自动分配和回收           | 存放于静态存储区                                         |
| 不会自动初始化                                 | 默认自动初始化为0                                        |
| 其他文件不能访问                               | 其他文件中使用extern修饰即可共享                         |

```c++
// f1.cpp
int a = 1;      // 全局

int main(){
	int b = 2;  //局部
	
	return 0;	
}

//f2
int main(){
	extern int a; //访问全局变量
}
```



## static

### 作用

   1. 修饰普通变量，修改变量的存储区域和生命周期，使变量存储在`静态存储区`。在编译时分配地址空间。如果有初始值就用初始值初始化它，如果没有初始值系统用默认值初始化它。静态`局部`变量作用域仍然在该代码块内，但是生命周期延长到了整个程序结束;静态`全局`变量的作用是将该全局变量的作用域限定到该文件，其他文件即使用 extern 声明也不能使用。
   2. 修饰普通函数，表明函数的作用范围，仅在定义该函数的文件内才能使用。在多人开发项目时，为了防止与他人命名空间里的函数重名，可以将函数定位为 static。
   3. 修饰成员变量，修饰成员变量使所有的对象只保存一个该变量，而且不需要生成对象就可以访问该成员。
   4. 修饰成员函数，修饰成员函数使得不需要生成对象就可以访问该函数，但是在 static 函数内不能访问非静态成员。



## this指针

1. `this` 指针是一个隐含于每一个非静态成员函数中的特殊指针。它指向调用该成员函数的那个对象。
2. 当对一个对象调用成员函数时，编译程序先将对象的地址赋给 `this` 指针，然后调用成员函数，每次成员函数存取数据成员时，都隐式使用 `this` 指针。
3. `this` 指针被隐含地声明为: `ClassName *const this`，这意味着不能给 `this` 指针赋值；在 `ClassName` 类的 `const` 成员函数中，`this` 指针的类型为：`const ClassName* const`，这说明 `this` 指针所指向的这种对象是不可修改的（即不能对这种对象的数据成员进行赋值操作）；
4. `this` 并不是一个常规变量，而是个右值，所以不能取得 `this` 的地址（不能 `&this`）。
6. 在以下场景中，经常需要显式引用`this`指针：
   1. 为实现对象的链式引用；
   2. 为避免对同一对象进行赋值操作；
   3. 在实现一些数据结构时，如 `list`。



## inline 内联函数

1. 编译器用于减少执行时间的优化技术
2. 编译器将内联函数的调用语句替换为函数代码本身，然后编译整个代码；因此编译器不必跳转到另一个位置来执行该函数，然后跳回
3. 优点是通过避免函数调用开销来加速程序，节省堆栈上变量push / pop的开销等
4. 增加了可执行文件的大小；内联在编译时，这意味着如果更改内联函数的代码，则需要使用它重新编译所有代码以确保它将更新
5. 通过inline关键词`建议`编译器将某函数内联，但决定权在编译器
6. 隐式内联：在类中`声明和定义`的除了虚函数的其他函数都是Inline



## 虚函数和内联

1. 虚函数可以是内联函数，但是当虚函数表现多态性的时候不能内联。
2. 内联是在`编译期`建议编译器内联，而虚函数的多态性在`运行期`，编译器无法知道运行期调用哪个代码，因此虚函数表现为多态性时（运行期）不可以内联。



## volatile

### [参考资料](https://v1otusc.github.io/2021/05/20/C++_Volatile_%E5%85%B3%E9%94%AE%E5%AD%97/)

1. volatile 关键字是一种类型修饰符，用它声明的类型变量表示可以被某些编译器未知的因素更改。所以编译器需要从内存地址从读取，而不是之前的某个缓存中读取。

   ```c++
   #include <stdio.h> 
   
   void main() {
     int i = 10;
     int a = i;
   
     printf("i = %d", b);
   
     // 下面的汇编的作用就是改变内存中 i 的值
     // 但是又不让编译器知道
     __asm {
       mov dword ptr [ebp-4], 20h
     } 
     
     int b = i;
     printf("i = %d", b);
   }
   ```

   Debug模式输出：

   ```c++
   i = 10
   i = 32
   ```

   Release模式输出：

   ```c++
   i = 10
   i = 10
   ```

   这表明，Release模式下，编译器以为i值没有修改，所以做了优化而导致了错误的结果。加入volatile关键字后：

   ```c++
   volatile int i = 10;
   ```

   Debug和Release模式都正确输出：

   ```c++
   i = 10
   i = 32
   ```

2. 一般用于：

   - 中断服务程序中修改的供其它程序检测的变量需要加 volatile；

   - 多线程间被几个任务共享的变量；

   - 状态寄存器一类的并行设备硬件寄存器，因为每次对它的读写都可能有不同的意义。

3. volatile指针：含义和const指针类似，有volatile指针和指针volatile的概念。

   - 修饰由指针指向的对象，数据是 const 或者 volatile 的：

   - 
   
     ```
     const char* cpch;
     volatile char* vpch;
     ```
   
   - 指针自身的值
   
     ```
     char* const pchc;
     char* volatile pchv;
     ```
   
     

## assert()

### 作用

- 断言，是宏，而非函数。作用是如果它的条件返回错误，则终止程序执行。可以通过定义 `NDEBUG` 来关闭 assert。



## sizeof()

- sizeof 对数组，得到整个数组所占空间大小。
- sizeof 对指针，得到指针本身所占空间大小。

- 返回值是`size_t`,在32位系统中位uint32，64位系统中为uint64。

## extern "C"

- 被 `extern "C"` 修饰的变量和函数是按照 C 语言方式编译和链接的。作用是让 C++ 编译器将 `extern "C"` 声明的代码当作 C 语言代码处理，可以避免 C++ 因符号修饰导致代码不能和C语言库中的符号进行链接的问题。

  如：

  ```
  extern "C"{
      #include <libavcodec/avcodec.h>
  }
  ```



## c++中struct和class

| struct                         | class                       |
| ------------------------------ | --------------------------- |
| 适合看成是一个数据结构的实现体 | 适合看成是一个对象的实现体  |
| 默认的继承访问权限为public     | 默认的继承访问权限为private |
| 默认的数据访问控制是public     | 默认的数据访问控制是private |



## explicit 

- 只能修饰只有一个参数的类构造函数。与之相对应的是默认情况下的implicit(隐式)。

- explicit 修饰构造函数时，可以防止隐式转换和复制初始化
- explicit 修饰转换函数时，可以防止隐式转换，但 [按语境转换](https://zh.cppreference.com/w/cpp/language/implicit_conversion) 除外



## friend 友元类和友元函数

### 友元函数

- 不是类的一部分，但又需要并且能够访问类的`私有（private）`成员和`保护（protected）`成员。

- 需要在类的定义中`声明`：

  ```c++
  friend 类型 函数名(形参);
  
  比如：
  class Student{
  private:
  	int m_age;
  public:
  	void setAge(int age);
  	friend void ShowAge(Student stu);  //声明在类中，但是不属于类的成员函数
  }
  ```

### 友元类

- 非继承，但是成员函数可以访问类的`私有`（甚至比继承的类权限还大）和`保护`成员；

- 友元类的所有成员函数都是另一个类的友元函数，都可以访问另一个类中的保护成员和私有成员。

- 声明方式：

  ```c++
  friend class 类名;
  
  class CA{
  public: 
      friend class CB;      //声明友元类CB
      void SetAge(int age);
  private:
      int m_age;
  }
  
  class CB{                 //CB类中的所有成员函数都可以访问CA中
  public:
      void ShowAge(CA a);
  }
  ```

### 注意

- 友元关系不能被继承
- 友元关系是单向的，不具有交换性 （A是B的友元，不代表B是A的友元）
- 友元关系不具有传递性 （A是B的友元，B是C的友元，不代表A是C的友元）
- 减少了类型检查和安全性检查，提高了程序的运行效率，但它破坏了类的封装性和隐藏性。



## using

### 声明

- 一条 `using 声明` 语句一次只引入命名空间的一个成员，如：

  > using std::cout;

### 指示

- 使得某个特定命名空间中所有名字都可见，如：

  > using namespace std;

### 注意

- 一般不要使用`using指示`，如果该特定命名空间中的名称和局部名称发生冲突，局部名称将覆盖名称空间版本，而编译器并不会发出警告。

- 使用 `using 声明` 更加明确和安全。



## ::范围解析运算符

1. 全局作用域符（`::name`）：用于类型名称（类、类成员、成员函数、变量等）前，表示作用域为`全局`命名空间
2. 类作用域符（`class::name`）：用于表示指定类型的作用域范围是该`class`类的
3. 命名空间作用域符（`namespace::name`）:用于表示指定类型的作用域范围是该`namespace`命名空间的



## enum枚举类型

- 一种派生数据类型，它是由用户定义的若干枚举`常量`的集合

- 枚举常量代表该枚举类型的变量可能取的值，编译系统为每个枚举常量指定一个整数值，默认状态下，这个整数就是所列举元素的序号，序号从0开始。如：

  ```c++
  enum fruit_set {apple, orange, banana=1, peach, grape}
  //枚举常量apple=0,orange=1, banana=1,peach=2,grape=3。
  
  enum week {Sun=7, Mon=1, Tue, Wed, Thu, Fri, Sat};
  //枚举常量Sun,Mon,Tue,Wed,Thu,Fri,Sat的值分别为7、1、2、3、4、5、6。
  ```

- 主要作用是增加程序可读性，比如用来描述状态量



## 初始化列表[code](./code/list_initialization/list_initialization.cpp)

- 只能用于类的构造函数，作用是避免给成员变量赋值，而是直接在类对象初始化的时候，从而提高效率。如：

  ```c++
  class CExample {
  public:
      int a;
      float b;
      //构造函数初始化列表
      CExample(): a(0),b(8.8)
      {}
      //构造函数内部赋值
      CExample()
      {
          a=0;
          b=8.8;
      }
  };
  ```

### 必须使用初始化列表而不是赋值的情况

1. 需要初始化const修饰的类成员

2. 需要初始化引用成员数据

3. 类成员包含没有默认构造函数的类类型

4. 类存在继承关系，派生类必须在其初始化列表中调用基类的构造函数

   ```c++
   class Base {
       int a, b;
   public:
       Base(int a, int b) : a(a), b(b) {}
   
       int getA() { return a; }
   };
   
   class extend : public Base {
       int x;
   public:
       explicit extend(int x) : x(x), Base(x, x) {} //继承类 构造函数
   };
   
   class example {
       int &a;
       const float b;
       Base c;
   public:
       example(int x, float y) : a(x), b(y), c(x, x) {
           std::cout << a << " " << b << std::endl;
           std::cout << c.getA();
       }
   };
   ```

   



## 面向对象三大特征-封装，继承，多态

### 封装

- 把客观事物封装成抽象的类，并且类可以把自己的数据和方法只让可信的类或者对象操作，对不可信的进行信息隐藏。提供了三种访问权限。

### 继承

- 新类从已有类那里得到已有的特性。原有的类称为基类或父类，产生的新类称为派生类或子类。

  - 单一继承：继承一个父类，这种继承称为单一继承，一般情况尽量使用单一继承
  - 继承多个父类，类与类之间要用逗号隔开，类名之前要有继承权限，假使两个或两个基类都有某变量或函数，在子类中调用时需要加类名限定符如c.a::i = 1；

- 继承也分为接口继承和实现继承：

  - 纯虚函数：不继承实现，只继承方法接口
  - 虚函数：继承方法接口，以及默认的实现
  - 普通函数：继承方法接口，以及强制的实现

- 继承后的权限：

  | 父类中访问权限 | 继承方式  | 子类中访问权限 |
  | -------------- | --------- | -------------- |
  | public         | public    | public         |
  | protected      | public    | protected      |
  | private        | public    | 不可访问       |
  | public         | protected | protected      |
  | protected      | protected | protected      |
  | private        | protected | 不可访问       |
  | public         | private   | private        |
  | protected      | private   | private        |
  | private        | private   | 不可访问       |

### 多态

- 可以简单概括为“一个接口，多种方法”，即用的是同一个接口，但是效果各不相同，多态有两种形式的多态，一种是静态多态，一种是动态多态。

  - 动态多态：也称为运行期多态。在基类中，把共同的功能声明为多个公共的`虚函数`接口，这里的接口称之为`显式接口`。各个子类`重写`这些虚函数，以完成具体的功能。客户端的代码（操作函数）通过指向`基类`的引用或指针来操作这些对象，对虚函数的调用会自动绑定到实际提供的子类对象上去。
  - 静态多态：也称为编译期多态。就是各自实现各自的功能，不需要基类，甚至可以没有任何关系。只需要各个具体类的实现中要求相同的接口声明，这里的接口称之为`隐式接口`。客户端把操作这些对象的函数定义为模板，当需要操作什么类型的对象时，直接对模板指定该类型实参即可（或通过实参演绎获得）。

- 面向对象编程中，以显式接口和运行期多态（虚函数）实现动态多态，在模板编程及泛型编程中，是以隐式接口和编译器多态来实现静态多态。

  | 静态多态                                       | 动态多态                             |
  | ---------------------------------------------- | ------------------------------------ |
  | 编译期完成，因此效率较高，编译器也可以进行优化 | 运行期绑定，导致一定程度的运行时开销 |
  | 模板定义接口，类型参数定义实现                 | 基类虚函数定义接口，继承类负责实现   |

- 可以将派生类的对象赋值给基类的指针或引用，反之不可以。

## 类成员的三种访问权限

1. public：可以被该类中的函数、子类的函数、友元函数访问，也可以由该类的对象访问；
2. private：可以被该类中的函数、友元函数访问，但不可以由子类的函数、该类的对象访问；
3. protected：可以被该类中的函数、子类的函数、友元函数访问，但不可以由该类的对象访问。



## 虚函数，纯虚函数

- 虚函数是c++实现动态多态的一个重要组成部分。核心理念就是通过基类访问派生类定义的函数，调用的函数是在运行期间而不是编译期间决定的。

- 声明方式是通过`virtual`关键词

  ```c++
  class base{
  public:
      virtual void vir_func(){}
  }
  ```

- 纯虚函数是不提供实现的虚函数，并且继承类必须实现这个函数。声明方式为：

  ```c++
  class base{
  public:
      virtual void vir_func() = 0；
  }
  ```

  | 虚函数                                                       | 纯虚函数                                           |
  | ------------------------------------------------------------ | -------------------------------------------------- |
  | 子类可以（也可以不）重新定义基类的虚函数，该行为称之为复写Override | 子类必须提供纯虚函数的实现                         |
  | 如果不提供虚函数的实现，将会自动调用基类的缺省虚函数实现     | 如果不提供纯虚函数的实现，编译将会失败             |
  | 允许子类通过重写来扩展或修改父类的实现                       | 可以为接口提供一个规范，子类必须实现这些接口       |
  | 任何类                                                       | 一个类中包含至少一个纯虚函数，那么这个类就是抽象类 |
  | 不能作为虚函数：普通函数（非类成员函数），静态函数（static），构造函数，内联函数 |                                                    |

### override标识符

- 告诉编译器这是重写的方法，如果方法不匹配，那么将无法通过编译。这是为了避免犯一些小错误导致重写失败，所以得明确这就是一个必须被重写的函数。

### final标识符

- 派生类无法重写基类的虚方法，如果派生类重写了基类虚方法，那么将无法编译

### 析构函数声明为虚函数

- 如果存在继承，虚函数最好声明为虚函数。否则删除一个实际指向派生类的`基类指针`，只会调用基类的析构函数，而不会调用派生类的析构函数以及派生类数据成员的析构函数。这样就可能造成内存泄露。

### 构造函数不能为虚函数

- 构造函数调用后才能产生虚表指针

- 但是虚函数在调用的时候需要由虚表指针，若构造函数为虚函数，那么调用构造函数的时候就需要现在还不存在的虚表指针，这就产生了冲突。

### 虚函数表

- 是一个函数查询表，以动态捆绑的方式解析函数调用。
- 每个具有一个或者多个虚函数的类都有一张虚表，这个表是在编译阶段建立的静态数组，其中包含了每个虚方法的函数指针，这些指针指向的是该类可见的派生最远的函数实现。
- 编译器会在基类对象添加一个隐含指针，称为`*__vptr`。当类的实例被创建时，这个指针指向该类所对应的虚表。
- 使用某个对象调用虚方法时，通过该指针查找虚表，然后根据实际的对象类型执行正确版本的方法调用。

- 例子：

  ```c++
  class Base
  {
  public:
      virtual void function1() { }
      virtual void function2() { }
  }
  
  class D1: public Base
  {
  public:
      virtual void function1() override { }
  }
  
  class D2: public Base
  {
  public:
      virtual void function2() override { }
  }
  ```

  包含三个类，其中派生类D1与D2分别重写了基类的function1()和function2()虚方法。编译器会相应地创建3个不同的虚表，分别对应每个类。而且编译器也会自动地为基类添加一个函数指针，如下所示：

  ```c++
  class Base
  {
  public:
      FunctionPointer *__vptr;
      virtual void function1() { }
      virtual void function2() { }
  }
  
  class D1: public Base
  {
  public:
      virtual void function1() override { }
  }
  
  class D2: public Base
  {
  public:
      virtual void function2() override { }
  }
  ```

  虚表为：

  ![虚表](./Image/VTable.gif)

### 纯虚函数和抽象类

- 包含纯虚函数的类就是抽象类
- 抽象类不能实例化
- 当继承一个抽象类时，必须重写所有纯虚函数才能实例化，否则继承出来的类也是一个抽象类

### 接口类

- 接口是一个抽象的概念，使用者只关注功能而不要求了解实现。一个接口类可以看成一些纯虚方法的集合，这意味着接口类仅有定义功能，而没有具体的实现。



## 堆和栈

| 栈                                                           | 堆                                                           |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| 由编译器自动分配释放，存放函数的参数值，局部变量的值等。其操作方式类似于数据结构中的栈。 | 一般由程序员分配释放，若程序员不释放，程序结束时可能由OS回收。它与数据结构中的堆是两回事，分配方式倒是类似于链表。 |
| 申请方式：由系统自动分配                                     | 申请方式：需要程序员自己申请，并指明大小                     |
| 向低地址扩展的数据结构，是一块连续的内存的区域；栈顶的地址和栈的最大容量是系统预先规定好的 | 堆是向高地址扩展的数据结构，是不连续的内存区域；堆的大小受限于计算机系统中有效的虚拟内存。由此可见，堆获得的空间比较灵活，也比较大。 |
| 不会产生内存碎片                                             | 可能造成大量的内存碎片                                       |



## 内存分配和管理 [ref](https://chenqx.github.io/2014/09/25/Cpp-Memory-Management/)

- `malloc` 和 `free`

  - 申请指定字节数的内存。申请到的内存中的初始值不确定。

  - 函数`malloc`的原型如下：

    ```c++
    void * malloc(size_t size);
    ```

  - 　用`malloc`申请一块长度为`length`的整数类型的内存，程序如下：

    ```c++
    int *p = (int *)malloc(sizeof(int) * length)
    ```

  - **类型转换**:`* malloc`返回值的类型是`void*`，所以在调用`malloc`时要显式地进行类型转换，将`void *`转换成所需要的指针类型。

  - **sizeof**: `* malloc`函数本身并不识别要申请的内存是什么类型，它只关心内存的`总字节数`。

  - `free`和`malloc`配对使用，负责释放由`malloc`申请的内存。

  - 函数`free`的原型如下：

    ```c++
    void free( void * memblock );
    ```

  - 指针`p`的类型以及它所指的内存的容量事先都是知道的，语句`free(p)`能正确地释放内存。

- `new` 和`delete`

  - `new`和`delete`的产生是由于`malloc`和`free`无法满足动态对象的要求。对象在创建的同时要自动执行构造函数，对象在消亡之前要自动执行析构函数。而对于`内部数据类型`而言，其没有构造和析构的过程，所以对它们来说`new，malloc`和`delete，free`是一样的。

  - 运算符`new`使用起来要比函数`malloc`简单得多，例如：

    ```c++
    int *p1 = (int *)malloc(sizeof(int) * length);
    int *p2 = new int[length];
    ```

  - 这是由于`new`内置了`sizeof`、类型转换和类型安全检查功能。对于非内部数据类型的对象而言，`new`在创建动态对象的同时完成了初始化工作。

  - new / new[]：完成两件事，先底层调用 malloc 分配了内存，然后调用构造函数（创建对象）。

  - delete/delete[]：也完成两件事，先调用析构函数（清理资源），然后底层调用 free 释放空间。

### 常见的内存错误及其对策

| 错误                                               | 对策                                             |
| -------------------------------------------------- | ------------------------------------------------ |
| 内存分配未成功，却使用了它                         | 在使用内存之前检查指针是否为`NULL`               |
| 内存分配虽然成功，但是尚未初始化就引用它           | 别忘了赋初值                                     |
| 内存分配成功并且已经初始化，但操作越过了内存的边界 | 注意分配的内存大小范围                           |
| 忘记了释放内存，造成内存泄露                       | 分配和释放要成对，或者使用智能指针去尽可能的避免 |
| 释放了内存却继续使用它                             |                                                  |



## 如何定义一个只能在堆上或栈上生成对象的类 [ref](https://www.nowcoder.com/questionTerminal/0a584aa13f804f3ea72b442a065a7618?)

- C++中，类的对象建立分为两种，一种是静态建立，如A a；另一种是动态建立，如A* ptr=new A；这两种方式是有区别的。
  - 静态建立：由编译器为对象在栈空间中分配内存，是通过直接移动栈顶指针，挪出适当的空间，然后在这片内存空间上调用构造函数形成一个栈对象。使用这种方法，直接调用类的构造函数。
  - 动态建立：是使用new运算符将对象建立在堆空间中。分为两步，第一步是执行operator new()函数，在堆空间中搜索合适的内存并进行分配；第二步是调用构造函数构造对象，初始化这片内存空间。这种方法，间接调用类的构造函数。

### 只能在堆上

- 将析构函数定义为私有。如果是静态建立一个对象，那么编译器就得掌握它整个生命周期但是由于析构函数是私有的，编译器无法调用，所以编译器会拒绝在栈空间上为类对象分配内存。

### 只能在栈上

- 将new和delete重载为私有。这样就不能动态建立一个对象。这个类的对象就是函数对象。函数对象是一个对象，但是使用的形式看起来像函数调用，实际上也执行了函数调用，因而得名。



<h2 id = “function_obj">函数对象类</h2>

- 如果一个类重载`()`操作符，那么这个类就叫做函数对象类。

  ```c++
  class CAverage
  {
  public:
      double operator()(int a1, int a2, int a3) //重载()运算符
      { 
          return (double)(a1 + a2 + a3) / 3;
      }
  };
  int main()
  {
      CAverage average;  //能够求三个整数平均数的函数对象
      cout << average(3, 2, 3);  //等价于 cout << average.operator(3, 2, 3);
      return 0;
  }
  ```

  

## c++11 的新特性 [ref](https://c.biancheng.net/view/7751.html)

### auto

- 自动类型推导，编译器会在编译期间自动推导出变量的类型，如：

  ```c++
  auto name = value;
  ```

- auto 仅仅是一个占位符，在编译器期间它会被真正的类型所替代。C++ 中的变量必须是有明确类型的，只是这个类型是由编译器自己推导出来的。

- 限制：不能在函数的参数中使用; 不能作用于类的非静态成员变量（也就是没有 static 关键字修饰的成员变量）中; 不能定义数组;不能作用于模板参数。
- 用途：定义迭代器方便；当不知道变量是什么类型，或者不希望指明具体类型的时候，比如泛型编程中。

### decltype

- 同样是用来在编译期间进行自动类型推导。

  ```c++
  decltype(exp) name = value;
  ```

- 根据exp表达式推导出变量的类型，和=右边的value无关。

- exp的结果必须有类型，不能是void。

### tuple

- 实例化的对象可以存储任意数量、任意类型的数据。因此可以用于存储多个不同类型的元素；或是函数需要返回多个不同的数据时，可以将数据存放在tuple中。

### initializer_list 列表初始化 [code](./code/initializer_list/initializer_list.cpp)

- 在C++11中，任意的STL容器都与和为显示指定长度的数组一样的初始化能力：

  ```c++
  int arr[] = { 1, 2, 3, 4, 5 };
  std::map < int, int > map_t { { 1, 2 }, { 3, 4 }, { 5, 6 }, { 7, 8 } };
  std::list<std::string> list_str{ "hello", "world", "china" };
  std::vector<double> vec_d { 0.0,0.1,0.2,0.3,0.4,0.5};
  ```

- 这种初始化的能力就是由initializer_list提供的，initializer_list可以接受任意长度的同类型数据的{……}

- 利用initializer_list的这种特性，可以让自己写的类也拥有接收可变长参数的能力：

  ```c++
  class FooVec {
  public:
      std::vector<int> m_vec;
  
      FooVec(std::initializer_list<int> list) {
          for (auto it = list.begin(); it != list.end(); it++)
              m_vec.push_back(*it);
          for (const auto &m: m_vec)
              std::cout << m << " ";
          std::cout << std::endl;
  
      }
  };
  ```

### lambda匿名函数 [code](./code/lambda/lambda.cpp)

- 定义的方法：

  ```c++
  [capture list] (params list) mutable exception-> return type { function body }
  
  1. capture list：捕获外部变量列表
  2. params list：形参列表
  3. mutable指示符：用来说明是否可以修改捕获的变量
  4. exception：异常设定，如noexcept/throw()
  5. return type：返回类型
  6. function body：函数体
  ```

- 可以省略某些部分来声明，如

  ```c++
  [capture list] (params list) -> return type { function body }
  const类型的表达式，不能修改捕获列表中的值；
      
  [capture list] (params list) {function body}
  返回值可以由函数体推导，如果函数体内由return语句，就根据返回值的类型确定；如果没有，返回值为void类型；
      
  [capture list] {function body}
  不需要参数。
  ```

- 各部分解释：

  - `capture list`: 可以捕获可见范围内的外部变量，捕获方式有：
    - 值捕获：被捕获的变量的值通过值拷贝的方式传入，函数体中不能修改该外部变量，可以理解传入之后就成为了const；
    - 引用捕获：引用捕获外部变量，只需要在捕获列表变量前面加上引用说明符&；
    - 隐式捕获：不需要显示的指定捕获哪些变量，而是由编译器判断。有两种方式分别是[=]和[&]。[=]表示以值捕获的方式捕获外部变量，[&]表示以引用捕获的方式捕获外部变量；
    - 混合方式：可以将不同的捕获方式混合起来。比如：[=, &x]代表变量x以引用形式捕获，其余变量以传值形式捕获。
  - `params list`: 不能有默认参数，不支持可变参数，所有参数必须有参数名
  - `mutable`: 可以修改值捕获的变量，不是指修改他原来对象的值，而是能修改拷贝的值。
  - `exception`: 如果使用，在之前的 () 小括号将不能省略（参数个数可以为 0）。默认情况下，lambda 函数的函数体中可以抛出任何类型的异常。而标注 noexcept 关键字，则表示函数体内不会抛出任何异常；使用 throw() 可以指定 lambda 函数内部可以抛出的异常类型。

### union [code](./code/union/union.cpp)

- 是一种节省空间的特殊的类，一个 union 可以有多个数据成员，但是在任意时刻只有一个数据成员可以有值。

- union的大小为最大的变量所占空间。

- union可以查看内存分布，比如查看一个int数字在内存中的样子：

  ```c++
  union U
  {
      unsigned char bits[4];
      int num;
  };
  
  
  int main()
  {
      U x;
      x.num = 64;
      for (int i = 0; i < 4; i++) {
          cout<<bitset<8>(x.bits[i]) << " ";
      }
      cout << endl;
      x.num = 114514;
      for (int i = 0; i < 4; i++) {
          cout << bitset<8>(x.bits[i]) << " ";
      }
  }
  ```

- 可以实现动态类型：

  ```c++
  struct var{
      union {
          int iv;
          double dv;
          char* sv;
      };
      var(const int& v) :iv{ v } {};
      var(const double& v) :dv{ v } {};
      var(const char* s) {
          int len = strlen(s);
          sv = new char[len + 1];
          memcpy(sv, s, len + 1);
      }
  };
  ```

### for循环

- 新的遍历方式：

  ```c++
  for (declaration : expression){
      //循环体
  }
  ```

- 除了使用方式的改变，最大的区别是这种新的遍历方式无法指定开始和结束位置，只能从头遍历到尾部，并且也不能知道当前的索引位置。

### constexpr [ref](https://learn.microsoft.com/en-us/cpp/cpp/constexpr-cpp?view=msvc-170)

- 常量表达式中的成员都是常量。因此常量表达式一旦确定，其值将无法修改。

- 常量表达式的计算往往发生在程序的编译阶段，只需要计算一次，大大提高了程序的执行效率。

- constexpr 关键字的功能是使指定的常量表达式获得在程序编译阶段计算出结果的能力，而不必等到程序运行阶段。

  |                                                              |                                                              |
  | ------------------------------------------------------------ | ------------------------------------------------------------ |
  | const修饰的变量可以在运行时初始化                            | constexpr修饰变量则必须在在编译期初始化，所有的constexpr变量都是const变量 |
  | const表示的是read only的语义，保证修饰的变量运行时不可以更改 | constexpr是名副其实的常量                                    |
  | 只能用于修饰变量，表明不可以改变                             | 还能被用于普通函数和类构造函数                               |

### long long超长整形

- long long是c++11标准新纳入的，虽然在这之前C99已经采纳并且已经有很多编译器有支持。
- c++11只限定了每种类型最少占用多少存储空间，不同的平台可以占用不同的存储空间。对long long 的要求是至少8个字节。

### 左值和右值

| 左值                                                       | 右值                                                         |
| ---------------------------------------------------------- | ------------------------------------------------------------ |
| lvalue不是left value而是local                              | rvalue不是right value而是read value                          |
| 既能够出现在等号左边，也能出现在等号右边                   | 只能出现在等号右边                                           |
| 可寻址的变量，有持久性                                     | 一般是不可寻址的常量，或在表达式求值过程中创建的无名临时对象，短暂性的 |
| 可以被赋值(非const等)                                      | 一般不能被赋值                                               |
| 可以隐式的转换为右值                                       | 不能隐式的转换为左值                                         |
| 变量名、函数名以及数据成员名，解引用表达式*ptr，++a，–-b等 | 非引用返回的临时变量、运算表达式产生的临时变量、原始字面量和lambda表达式，a++，b--等 |

### 左值引用和右值引用[code](./code/rvalueRef/rvalueRef.cpp)

#### 含义

1. 使用`&`定义左值引用，实际上是一个别名。不能将一个右值赋值给（非常量的）左值引用：

   > std::string& sref = std::string();       // 错误: 非常量的引用 'std::string&' 错误地使用右值 'std::string` 初始化
   >
   > const std::string& sref = std::string(); //正确

但是常量的左值引用可以使用右值赋值。因为无法通过常量的引用修改变量的值，也就不会出现修改了右值的情况。

2. 使用`&&`定义右值引用,可以延长右值的生命周期。右值引用本身是左值。主要是解决两个问题：临时对象非必要的昂贵的拷贝操作和模板函数中如何按照参数的实际类型进行转发。

   > int &&a = 10;   //可以对a取地址

- [四行代码看右值引用](https://www.cnblogs.com/qicosmos/p/4283455.html)

```c++
第一行代码： int i = getVar();
// 上面的这行代码从getVar()函数获取一个整形值。 其中i为左值，函数getVar()返回的临时值，然后拷贝给i，但是这个临时值在表达式结束后被销毁。

第二行代码： T&& k = getVar();
// getVar()产生的临时值不会像第一行代码那样，在表达式结束之后就销毁了，而是会被“续命”，他的生命周期将会通过右值引用得以延续，和变量k的声明周期一样长，并且不会再拷贝一次。

第三行代码： T(T&& a) : m_val(val){ a.m_val=nullptr;}
// 这是一个类的构造函数，构造函数的参数是一个右值引用。
// 一个带有堆内存的类，必须提供一个深拷贝拷贝构造函数，因为默认的拷贝构造函数是浅拷贝，会发生“指针悬挂”的问题，内部的堆内存可能被删除多次而导致错误。但是有时这种深拷贝是没有必要且浪费性能的，避免的方式就是通过第三行代码实现的 移动 构造函数。
// 移动构造函数不会做深拷贝，仅仅是将指针的所有者转移到了另外一个对象。从而解决了前面提到的临时变量拷贝构造产生的性能损失的问题。这就是所谓的移动语义，右值引用的一个重要作用是用来支持移动语义的。
// 移动语义是通过右值引用来匹配临时值的，并且普通的左值也能借助移动语义来优化性能，C++11为了解决这个问题，提供了std::move方法来将左值转换为右值，从而方便应用移动语义。move是将对象资源的所有权从一个对象转移到另一个对象，只是转移，没有内存的拷贝，这就是所谓的move语义。

第四行代码： template <typename T>
           void f(T&& val){ foo(std::forward<T>(val)); }
// 完美转发：在函数模板中，完全依照模板的参数的类型（即保持参数的左值、右值特征），将参数传递给函数模板中调用的另外一个函数。C++11中的std::forward正是做这个事情的，他会按照参数的实际类型进行转发。
```

### move() [code](./code/move/move.cpp)

- 移动构造函数的调用时机是：用同类的`右值`对象初始化新对象。那么，用当前类的左值对象（有名称，能获取其存储地址的实例对象）初始化同类对象时，是否就无法调用移动构造函数了呢？当然不是，C++11 标准中已经给出了解决方案，即调用 move() 函数。

  

### 引用限定

- 默认情况下，类中用 public 修饰的成员函数，既可以被左值对象调用，也可以被右值对象调用。

- 可以通过添加`&`或`&&`限定符去限定成员函数的调用者是左值还是右值：

  ```c++
  class demo {
  public:
      demo(int num):num(num){}
      int get_num()&{
          return this->num;
      }
      int get_num1() &&{
          return this->num + 1;
      }
  private:
      int num;
  };
  ```

- 如果const也修饰成员函数，那么引用限定符得放在const后面，如：

  ```c++
  int get_num() const &{
  	return this->num;
  }
  ```

- `const &` 左值和右值对象都能调用；`const &&`只能右值对象调用。 

### 智能指针 [code](./code/smart_ptr/smart_ptr.cpp)

- 内存管理不当可能造成严重的问题，如：
  - 有些内存资源已经被释放，但指向它的指针并没有改变指向（成为了野指针），并且后续还在使用；
  - 有些内存资源已经被释放，后期又试图再释放一次（重复释放同一块内存会导致程序运行崩溃）；
  - 没有及时释放不再使用的内存资源，造成内存泄漏，程序占用的内存资源越来越多。
- 引入智能指针可以在适当时机自动释放分配的内存。

#### shared_ptr [参考实现](https://www.cnblogs.com/tianshihao/p/14378918.html)

- shared_ptr 智能指针可以共同使用同一块堆内存。采取引用计数机制，一个 shared_ptr 指针放弃了堆内存的“使用权”会让引用计数减 1，只有引用计数为 0 时，堆内存才会被自动释放。

- 如果构造的shared_ptr是空的，那么初始引用计数为0：

  ```c++
  std::shared_ptr<int> p1;
  std::shared_ptr<int> p2(nullptr);
  ```

- 也可以明确指向的构造，初始引用计数为1：

  ```c++
  std::shared_ptr<int> p3(new int(10));
  std::shared_ptr<int> p3 = std::make_shared<int>(10);  //更推荐
  ```

- shared_ptr提供了拷贝构造函数，如果当前引用计数不为0，那么使用后引用计数加1：

  ```c++
  //调用拷贝构造函数
  std::shared_ptr<int> p4(p3);  //p4和p3都指向同一块堆内存
  ```

- shared_ptr提供了移动构造函数，转让内存的所有权，引用计数不会改变,并且被移动的指针会成为空指针：

  ```c++
  //调用移动构造函数
  std::shared_ptr<int> p5(std::move(p4));
  ```

- 初始化 shared_ptr 智能指针时，可以自定义所指堆内存的释放规则；

#### unique_ptr

- unique_ptr 指针指向的堆内存无法同其它 unique_ptr 共享，也就是说，每个 unique_ptr 指针都独自拥有对其所指堆内存空间的所有权。

  ```c++
  std::unique_ptr<int> u1();
  std::unique_ptr<int> u2(nullptr);
  std::unique_ptr<int> u3(new int);
  std::unique_ptr<int> u4 = std::make_unique<int>(3);
  ```

  

- 由于unique_ptr不能共享，所以它只提供了构造函数和移动构造函数, 不能进行拷贝操作。

  ```c++
  std::unique_ptr<int> u5(u4);//错误，堆内存不共享
  std::unique_ptr<int> u5(std::move(u4));//正确，调用移动构造函数
  ```

- 同样可以自定义释放规则，但是只能采取[函数对象类](#函数对象类)的方式；

  ```c++
  struct myDel
  {
      void operator()(int *p) {
          delete p;
      }
  };
  std::unique_ptr<int, myDel> p6(new int);
  ```

#### weak_ptr [ref](https://www.cnblogs.com/JCpeng/p/15058214.html)

- 通常不单独使用（没有实际用处），只能和 shared_ptr 类型指针搭配使用。甚至可以将 weak_ptr 类型指针视为 shared_ptr 指针的一种辅助工具，借助 weak_ptr 类型指针， 我们可以获取 shared_ptr 指针的一些状态信息，比如有多少指向相同的 shared_ptr 指针、shared_ptr 指针指向的堆内存是否已经被释放等等。

- weak_ptr类型指针的指向和某一 shared_ptr 指针相同时，weak_ptr 指针并不会使所指堆内存的引用计数加 1;当 weak_ptr 指针被释放时，之前所指堆内存的引用计数也不会因此而减 1。

- weak_ptr的主要作用是解决shared_ptr的`[循环引用]`问题。

  - 循环引用指的是两个对象A，B，都有一个数据成员为share_ptr并且互相指向彼此。这样就会导致引用计数为2，当前函数退出后，只会将引用计数减1，导致堆内存没有释放掉。

- 基本的使用方式：

  ```c++
  std::shared_ptr<int> sp1(new int(10));
  std::shared_ptr<int> sp2(sp1);
  std::weak_ptr<int> wp(sp2);
  //输出和 wp 同指向的 shared_ptr 类型指针的数量
  cout << wp.use_count() << endl;
  //释放 sp2
  sp2.reset();
  cout << wp.use_count() << endl;
  //借助 lock() 函数，返回一个和 wp 同指向的 shared_ptr 类型指针，获取其存储的数据
  cout << *(wp.lock()) << endl;
  return 0;
  ```




## 强制类型转换运算符 [code](./code/cast/cast.cpp)

- c语言中也有强制类型转换，出于对以下问题的考虑，c++引入了强制类型转换机制：

  1. c语言没有从形式上体现转换功能和风险的不同
  2. c语言将多态基类指针转换成派生类指针时不检查安全性，即无法判断转换后的指针是否确实指向一个派生类对象
  3. c语言难以在程序中寻找到底什么地方进行了强制类型转换

- C++ 强制类型转换运算符的用法如下：

  ```
  强制类型转换运算符 <要转换到的类型> (待转换的表达式)
  ```

  如：

  ```c++
  double d = static_cast <double> (3*5);  //将 3*5 的值转换成实数
  ```

### static_cast

- 用于进行比较“自然”和低风险的转换，如`整型`和`浮点型`、`字符型`之间的互相转换。如果对象所属的类`重载`了`强制类型转换运算符 T`（如 T 是 int、int* 或其他类型名），则 static_cast 也能用来进行对象到 T 类型的转换。
- 不能用于在`不同类型的指针`之间互相转换，也不能用于`整型`和`指针`之间的互相转换，当然也不能用于不同类型的`引用`之间的转换。因为这些属于风险比较高的转换。

### reinterpret_cast

- 用于进行各种`不同类型的指针`之间、`不同类型的引用`之间以及`指针和能容纳指针的整数类型`之间的转换。转换时，执行的是逐个比特复制的操作。

### const_cast

- 用于进行去除 const 属性的转换。

### dynamic_cast

- 用于将多态`基类`的指针或引用强制转换为`派生类`的指针或引用，而且能够检查转换的`安全性`。对于不安全的指针转换，转换结果返回 NULL 指针。





# Effective C++

## 视 C++ 为一个语言联邦（C、Object-Oriented C++、Template C++、STL）











# STL [ref](https://c.biancheng.net/stl/)

- STL全称为 standard template library，即标准模板库或泛型库。其包含有大量的模板类和模板函数。

- 由容器、算法、迭代器、函数对象、适配器、内存分配器这 6 部分构成，其中后面 4 部分是为前 2 部分服务的。

  | 组成                       | 含义                                                         |
  | -------------------------- | ------------------------------------------------------------ |
  | 容器(containers)           | 一些封装[数据结构](https://c.biancheng.net/data_structure/)的模板类，例如 vector 向量容器、list 列表容器等。 |
  | 算法(algorithms)           | 非常多（大约 100 个）的数据结构算法，它们都被设计成一个个的模板函数，这些算法在 std 命名空间中定义，其中大部分算法都包含在头文件 <algorithm> 中，少部分位于头文件 <numeric> 中. |
  | 迭代器(iterators)          | 对容器中数据的读和写，是通过迭代器完成的，它扮演着容器和算法之间的胶合剂。 |
  | 函数对象(function objects) | 如果一个类将 () 运算符重载为成员函数，这个类就称为函数对象类，这个类的对象就是函数对象（又称仿函数）。 |
  | 适配器(adaptor)            | 可以使一个类的接口（模板的参数）适配成用户指定的形式，从而让原本不能在一起工作的两个类工作在一起。容器、迭代器和函数都有适配器。 |
  | 内存分配器(allocator)      | 为容器类模板提供自定义的内存申请和释放功能，由于往往只有高级用户才有改变内存分配策略的需求，因此内存分配器对于一般用户来说，并不常用。 |



## 容器

- 一些模板类的集合，和普通模板类不同的是，容器中封装的是组织数据的方法（也就是数据结构）。

- 可以分为序列容器，排序容器和哈希容器，后两类有时也统称为关联容器。

  | 容器种类                        | 功能                                                         |
  | ------------------------------- | ------------------------------------------------------------ |
  | 序列容器(sequence container)    | 主要包括 vector 向量容器、list 列表容器以及 deque 双端队列容器。之所以被称为序列容器，是因为元素在容器中的位置同元素的值无关，即容器不是排序的。将元素插入容器时，指定在什么位置，元素就会位于什么位置。 |
  | 关联容器(associative container) | 包括 set 集合容器、multiset多重集合容器、map映射容器以及 multimap 多重映射容器。排序容器中的元素默认是由小到大排序好的，即便是插入元素，元素也会插入到适当位置。所以关联容器在查找时具有非常好的性能。 |
  | 无序关联式容器                  | `C++ 11` 新加入 4 种关联式容器，分别是 unordered_set 哈希集合、unordered_multiset 哈希多重集合、unordered_map 哈希映射以及 unordered_multimap 哈希多重映射。和排序容器不同，哈希容器中的元素是未排序的，元素的位置由哈希函数确定。 |

### 序列容器

| 容器名                   | 特点                                                         |
| ------------------------ | ------------------------------------------------------------ |
| array<T,N> 数组          | 存储 N 个 T 类型的元素，建立后长度固定不变的，不能增加或删除元素，只能改变某个元素的值 |
| vector<T> 向量           | 存放 T 类型的元素，是一个长度可变的序列容器，在存储空间不足时，会自动申请更多的内存。在尾部增加或删除元素的时间复杂度为 O(1)，在其它位置插入或删除元素时间复杂度为 O(n) |
| deque<T> 双端队列        | 和vector类似，区别在于不仅尾部插入和删除元素高效，在头部插入或删除元素也同样时间复杂度都是 O(1) |
| list<T> 链表             | 长度可变的、由 T 类型元素组成的序列，它以双向链表的形式组织元素，在这个序列的任何地方都可以高效地增加或删除元素，时间复杂度都为O(1），但访问容器中任意元素的速度要比前三种容器慢，这是因为 list<T> 必须从第一个元素或最后一个元素开始访问，需要沿着链表移动，直到到达想要的元素。 |
| forward_list<T> 正向链表 | 和 list 容器非常类似，只不过它以单链表的形式组织元素，它内部的元素只能从第一个元素开始访问，是一类比链表容器快、更节省内存的容器。 |

#### array

- 可以将array当作是普通数组的升级版，普通数组能做的事，array都可以做。并且安全性更好，也不会损失效率。

#### vector [code](./code/vector/vector.cpp)

- vector同样可以看作是普通数组升级版，和array不同的是，vector可以动态调整数组大小。
- vector中size()和capacity()的区别：size()指的是当前以及存放了多少元素， capacity()指的是目前申请的内存空间可以存放多少元素。
- resize()同时修改size和capacity，并且会创建对象；reserve()只修改capacity，且不会创建对象。
- push_back()和emplace_back()都可以添加对象到尾部。区别在于，push_back()会先创建一个元素，然后将这个元素再拷贝或移动(优先)到容器中（如果是拷贝，事后会自行销毁先前创建的这个元素）；而 emplace_back()则是直接在容器尾部创建这个元素，省去了拷贝或移动元素的过程。因此，优先考虑使用emplace_back()，效率更高。
- insert()和emplace()是在指定位置插入元素，区别和上一代类似。

#### deque [code](./code/deque/deque.cpp)

- 和vector相比较，多了可以在头部直接增加或删除元素的特性和相应的函数。
- [底层实现](https://c.biancheng.net/view/6908.html)是用由一段一段等长的连续空间构成，各段空间之间并不一定是连续的，可以位于在内存的不同区域。
- 在deque的头部增添一个元素会使整体的索引值都加1。

#### list

- [底层实现](https://c.biancheng.net/view/6955.html)用非连续的内存块依次链接而成

#### forward_list

- 和list相比较，底层实现同样是链表结构，但是是单向的。好处在于只需要单向时，单链表耗用的内存空间更少，空间利用率更高，并且对于实现某些操作单链表的执行效率也更高。

### 关联容器

| 名称     | 特点                                                         |
| -------- | ------------------------------------------------------------ |
| map      | 各个元素的键必须是唯一的（即不能重复），该容器会根据各元素键的大小，默认进行升序排序 |
| set      | 各个元素键和值完全相同，且各个元素的值不能重复（保证了各元素键的唯一性）。该容器会自动根据各个元素的键（其实也就是元素值）的大小进行升序排序 |
| multimap | 和 map 容器唯一的不同在于，multimap 容器中存储元素的键可以重复 |
| multiset | 和 set 容器唯一的不同在于，multiset 容器中存储元素的值可以重复（一旦值重复，则意味着键也是重复的） |

#### pair

- 关联式容器存储的数据都是`键值对`，c++提供了pair类模板来将两个普通元素组成<first，second>可以作为键值对。

#### map

- 键值对的键和值可以是任意数据类型，包括 C++基本数据类型（int、double 等）、结构体或类自定义的类型。
- map的键不能重复也不能被修改，并且就是根据键来进行排序，可以自定义排序规则。

#### multimap

- multimap和map的区别在于，可以存储多个键相同的键值对。
- 未提供 at() 成员方法，也没有重载 [] 运算符，因为一个键可能对应多个值。
- 遍历方法：
  - 可以使用find(key)方法找到第一个键为key的键值对，count(key)找到键为key的键值对数量，然后遍历。
  - 使用lower_bound(key)和upper_bound(key)分别指向键为key的首个元素迭代器，最后元素的后一个迭代器。若不存在则两个迭代器相等。
  - 使用equal_range(key)返回一个pair，pair里的内容和上一点一样。

#### set

- set的key和value相等。
- 未提供at() 成员函数，也未对 [] 运算符进行重载。因此，要想访问 set 容器中存储的元素，只能借助 set 容器的迭代器。

#### multiset

- 和set的区别在于，可以存储多个键相同的键值对。

#### 如何修改关联式容器中键值对的键

- 可以采用同一种解决思路，即先删除该键值对，然后再向容器中添加修改之后的新键值对。
- map，multimap中的键为const，无法修改；set，multiset并没有限定为const，但是一定不要直接修改set中元素的值。

### 无序关联式容器

- 和关联容器的区别在于：关联容器底层实现采用的树存储结构，更确切的说是红黑树结构；而无序关联式容器底层是采用的哈希表。
- 正是由于不同的底层结构，所以无序关联式容器具有以下两个特点：
  - 内部存储的键值对是无序的，各键值对的存储位置取决于该键值对中的键
  - 指定键查找对应的值平均时间复杂度为 O(1)

| 名称               | 特点                                                         |
| ------------------ | ------------------------------------------------------------ |
| unordered_map      | 存储键值对 <key, value> 类型的元素，其中各个键值对键的值不允许重复，且该容器中存储的键值对是无序的。 |
| unordered_multimap | 和 unordered_map 唯一的区别在于，该容器允许存储多个键相同的键值对。 |
| unordered_set      | 不再以键值对的形式存储数据，而是直接存储数据元素本身（当然也可以理解为，该容器存储的全部都是键 key 和值 value 相等的键值对，正因为它们相等，因此只存储 value 即可）。另外，该容器存储的元素不能重复，且容器内部存储的元素也是无序的。 |
| unordered_multiset | 和 unordered_set 唯一的区别在于，该容器允许存储值相同的元素。 |

- 无序关联式容器和关联式容器的使用方法基本相同，如何选择这两种容器呢：
  - 如果涉及大量遍历容器的操作，建议首选关联式容器；
  - 反之，如果更多的操作是通过键获取对应的值，则应首选无序关联式容器。



## 容器适配器

- 封装了序列容器的类模板，它在一般序列容器的基础上提供了一些不同的功能。之所以称作适配器类，是因为它可以通过适配容器现有的接口来提供不同的功能。

| 适配器            | 特点                                                         |
| ----------------- | ------------------------------------------------------------ |
| stack<T>          | 封装了 deque<T> 容器,默认实现为一个后入先出(Last-In-First-Out，LIFO)的栈 |
| queue<T>          | 封装了 deque<T> 容器,默认实现为一个先入先出(First-In-First-Out，FIFO)的队列 |
| priority_queue<T> | 封装了 vector<T> 容器，默认实现的是一个会对元素排序，从而保证最大元素总在队列最前面的队列。 |

- 简单理解适配器，就是将不适用的序列式容器（包括 vector、deque 和 list）变得适用。通过封装某个序列式容器，并重新组合该容器中包含的成员函数，使其满足某些特定场景的需要。

### stack

- 实现栈的操作

### queue

- 实现队列

### priority_queue

- 优先级队列，每次出队的都是优先级最大的元素，优先级的评定由创建时指定的排序规则决定。
- 底层容器为vector，但是数据结构是采用堆，这样能保证最大或者最小的元素在首位。 [如何利用vector实现堆](https://blog.csdn.net/peachzy/article/details/117958932)



## 迭代器 [ref](https://c.biancheng.net/view/6675.html)

- 一个类似中介的装置，它除了要具有对容器进行遍历读写数据的能力之外，还要能对外隐藏容器的内部差异，从而以统一的界面向算法传送数据。

- 可以分为输入迭代器、输出迭代器、前向迭代器、双向迭代器、随机访问迭代器 5 种。

  - 输入迭代器、输出迭代器比较特殊，它不是把数组或容器当做操作对象，而是把输入流/输出流作为操作对象。
  - 前向迭代器：支持++，*，复制和赋值操作，==和!=比较操作。使用者有forward_list，unordered_map / unordered_multimap，unordered_set / unordered_multiset。
  - 双向迭代器：具有前向迭代器的所有功能，以及- -操作。使用者有list，set / multiset，map / multimap。
  - 随机访问迭代器：具有双向迭代器的全部功能，以及+=，-=，+，-，[]操作。使用者有array，vector，deque。

- 迭代器的定义方式：

  | 定义方式       | 具体格式                                   |
  | -------------- | ------------------------------------------ |
  | 正向迭代器     | 容器类名::iterator 迭代器名;               |
  | 常量正向迭代器 | 容器类名::const_iterator 迭代器名;         |
  | 反向迭代器     | 容器类名::reverse_iterator 迭代器名;       |
  | 常量反向迭代器 | 容器类名::const_reverse_iterator 迭代器名; |




## 迭代器适配器 [code](./code/iterator/iterator.cpp)

- 本质也是一个模板类，比较特殊的是，该模板类是借助基础迭代器实现的。换句话说，迭代器适配器模板类的内部实现，是通过对以上 5 种基础迭代器拥有的成员方法进行整合、修改，甚至为了实现某些功能还会添加一些新的成员方法。

| 名称                                                         | 功能                                                         |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| 反向迭代器（reverse_iterator）                               | 内部重新定义了递增运算符（++）和递减运算符（--），专门用来实现对容器的逆序遍历。 |
| 插入型迭代器（inserter或者insert_iterator）                  | 用于在容器的任何位置添加新的元素，此类迭代器不能被运用到元素个数固定的容器（比如 array）上。 |
| 流迭代器（istream_iterator / ostream_iterator）流缓冲区迭代器（istreambuf_iterator / ostreambuf_iterator） | 输入流迭代器用于从文件或者键盘读取数据；相反，输出流迭代器用于将数据输出到文件或者屏幕上。<br/>输入流缓冲区迭代器用于从输入缓冲区中逐个读取数据；输出流缓冲区迭代器用于将数据逐个写入输出流缓冲区。 |
| 移动迭代器（move_iterator）                                  | 可以将某个范围的类对象移动到目标范围，而不需要通过拷贝去移动。 |

### 反向迭代器

- 常用来对容器进行反向遍历，即从容器中存储的最后一个元素开始，一直遍历到第一个元素。
  - 当反向迭代器执行 ++ 运算时，底层的基础迭代器实则在执行 -- 操作，意味着反向迭代器在反向遍历容器；
  - 当反向迭代器执行 -- 运算时，底层的基础迭代器实则在执行 ++ 操作，意味着反向迭代器在正向遍历容器。

### 插入型迭代器

- 功能就是向指定容器中插入元素。底层是要调用容器的插入函数的。

| 名称                  | 功能                                                         |
| --------------------- | ------------------------------------------------------------ |
| back_insert_iterator  | 在指定容器的尾部插入新元素，但前提必须是提供有 push_back() 成员方法的容器（包括 vector、deque 和 list）。 |
| front_insert_iterator | 在指定容器的头部插入新元素，但前提必须是提供有 push_front() 成员方法的容器（包括 list、deque 和 forward_list）。 |
| insert_iterator       | 在容器的指定位置之前插入新元素，前提是该容器必须提供有 insert() 成员方法。 |



## 常用算法 [ref](https://c.biancheng.net/stl/algorithms/)

### 排序算法







# Cmake

- 是一个跨平台的安装（编译）工具，可以用简单的语句来描述所有平台的安装(编译过程)。他能够输出各种各样的makefile或者project文件，能测试编译器所支持的C++特性,类似UNIX下的automake。
- 编辑CmakeLists.txt文件，通过cmake后会自动生成Makefile文件，然后就能通过此Makefile文件生成可执行文件。

## cmake_minimum_required()

- 表示cmake的最低版本，这是每个cmakeLists文件都需要的,如

  ```cmake
  cmake_minimum_required(VERSION 3.12)
  ```

## project()

- 指定的文件名，可以通过变量 ${PROJECT_NAME}使用，如

  ```cmake
  project("VirtualBackground" VERSION 1.1.9)
  ```

## set()

- 可以用来给变量赋值，如：

  ```cmake
  set(TARGET_NAME "VirtualBackground.${PROJECT_VERSION}")
  ```

- 还可以用来设置C++版本，编译标志等。

## include()

- 可以将其他CMake 脚本文件或cmake 宏文件包含到当前的CMakeLists.txt 文件中，如：

  ```cmake
  include(./xxx.cmake)  //这个.cmake文件中可以包含一些本地库的路径以供检索
  ```

## find_package()

- 可以用于引入外部依赖包，它会搜寻`${CMAKE_PREFIX_PATH}`路径去找到类似`xxConfig.cmake`,`xx-config.cmake`的配置文件，这些配置文件中必须要要包含由include，library的路径信息，如
- 使用 `find_package(OpenCv REQUIRED)`就会到`${CMAKE_PREFIX_PATH}`路径下去寻找到`OpenCVConfig.cmake`文件，这个文件里包含了`OpenCV_INCLUDE_DIRS`,`OpenCV_LIBS`的信息，就可以用这些信息来构建工程。

## find_path()

- 指定需要搜索到的头文并命名，会搜索`${CMAKE_INCLUDE_PATH}`路径，如

  ```cmake
  find_path(FFMPEG_INCLUDE_DIR libavcodec/avcodec.h REQUIRED)
  ```

## find_library()

- 指定需要搜索到的链接库并命名，会搜索`${CMAKE_LIBRARY_PATH}`路径，如

  ```cmake
  find_library(AVCODEC_LIBRARY avcodec REQUIRED)
  ```

## include_directories()

- 用于将本工程中的头文件引入

## aux_source_directory()

- 用于将指定目录下的所有源文件自动添加到一个变量中，以便于后续的编译和构建过程。如：

  ```cmake
  aux_source_directory(./src/job CPPLIST) //就可以将job目录下的所有源文件加入 CPPLIST，之后只用CPPLIST用于编译构建
  ```

## add_executable()

- 用于将 源文件列表中列出的文件生成可执行文件。如：

  ```cmake
  add_excutable(${project_name}
  	${CPPLIST}
  	main.cpp
  	)
  ```

## target_include_directories()

- 指定目标包含的头文件路径,可以将之前通过find_path()搜索到一些需要的头文件引入。如：

  ```cmake
  target_include_directories(${project_name}
  	PRIVATE
  	${FFMPEG_INCLUDE_DIR}	
  )
  ```

## target_link_libraries()

- 指定目标链接的库，可以将之前通过find_library()搜索到一些需要的库文件引入。如：

  ```
  target_link_libraries{${PROJECT_NAME}
  	PRIVATE
  	${AVCODEC_LIBRARY}	
  }
  ```









# 计算机网络

## 一些协议

### HTTP(Hyper Text Transfer Protocol)超文本传输协议 [ref](https://www.cnblogs.com/ranyonsue/p/5984001.html)

- ​	











































# 操作系统

# 数据库

# 数据结构

# 计算机组成

