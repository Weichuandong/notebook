//
// Created by weichuandong on 2023/12/5.
//
#include "iostream"
#include "functional"

using std::function;

int main() {
//    int a = 1;
//    auto f = [a]() mutable {
//        a++;
//        std::cout << a << std::endl;
//    };
//    f();
//    std::cout << a;
    int m = [](int x) { return [](int y) { return y * 2; }(x) + 6; }(5);
    std::cout << "m:" << m << std::endl;           //输出m:16

    std::cout << "n:" << [](int x, int y) { return x + y; }(5, 4) << std::endl;           //输出n:9

    auto gFunc = [](int x) -> function<int(int)> { return [=](int y) { return x + y; }; };
    auto lFunc = gFunc(4);
    std::cout << lFunc(5) << std::endl;

    auto hFunc = [](const function<int(int)> &f, int z) { return f(z) + 1; };
    auto i = hFunc(gFunc(7), 8);
    std::cout << i << std::endl;
    int a = 111, b = 222;
    auto func = [=, &b]()mutable {
        a = 22;
        b = 333;
        std::cout << "a:" << a << " b:" << b << std::endl;
    };

    func();
    std::cout << "a:" << a << " b:" << b << std::endl;

    a = 333;
    auto func2 = [=, &a] {
        a = 444;
        std::cout << "a:" << a << " b:" << b << std::endl;
    };
    func2();

    auto func3 = [](int x) -> function<int(int)> { return [=](int y) { return x + y; }; };
    std::function<void(int x)> f_display_42 = [](int x) { std::cout << x << std::endl; };
    f_display_42(44);
}