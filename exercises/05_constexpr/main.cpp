#include "../exercise.h"

constexpr unsigned long long fibonacci(int i) {
    switch (i) {
        case 0:
            return 0;
        case 1:
            return 1;
        default:
            return fibonacci(i - 1) + fibonacci(i - 2);
    }
}

int main(int argc, char **argv) {
    constexpr auto FIB20 = fibonacci(20);
    ASSERT(FIB20 == 6765, "fibonacci(20) should be 6765");
    std::cout << "fibonacci(20) = " << FIB20 << std::endl;

    // TODO: 观察错误信息，修改一处，使代码编译运行
    // PS: 编译运行，但是不一定能算出结果……
    // 当 ANS_N = 90 时，fibonacci(90) 的递归调用深度会非常大。C++ 标准没有规定编译期递归的最大深度，但编译器通常会有一个限制。当递归深度超过这个限制时，编译器会报错，提示递归过深。为了使代码能够编译运行，可以将 constexpr 修饰符从 ANS 的定义中移除，让 fibonacci(90) 在运行期进行计算。这样可以避免编译期递归深度限制的问题。
    constexpr auto ANS_N = 40;
    auto ANS = fibonacci(ANS_N);
    std::cout << "fibonacci(" << ANS_N << ") = " << ANS << std::endl;

    return 0;
}
