#include "../exercise.h"

// READ: `static` 关键字 <https://zh.cppreference.com/w/cpp/language/storage_duration>
// THINK: 这个函数的两个 `static` 各自的作用是什么？
// 1. 第一个 static：修饰函数 func（static int func(...)）
// 作用：限制函数的作用域，仅在当前编译单元（.c/.cpp 文件）内可见。
// 默认情况下，C/C++ 的函数是 “外部链接” 的（可通过 extern 声明，在其他文件中调用）。
// 加 static 后，函数变为 “内部链接”：只能在定义它的 .c/.cpp 文件中被调用，其他文件即使声明也无法访问（避免函数名冲突，常用于封装文件内部的工具函数）。
// 2. 第二个 static：修饰局部变量 static_（static int static_ = param）
// 作用：改变局部变量的存储周期，使其从 “栈存储” 变为 “静态存储”，且只初始化一次。
// 普通局部变量（无 static）：存储在栈区，函数调用结束后立即销毁，每次调用都会重新初始化。
// 加 static 后：
// 存储位置转移到 “静态存储区”（与全局变量同区域），函数调用结束后不会销毁，值会保留到下次调用；
// 初始化行为仅执行 一次（首次调用函数时初始化），后续调用不再重新赋值（即使右边是 param，也只会用首次调用的 param 初始化 static_）。
static int func(int param) {
    static int static_ = param;
    // std::cout << "static_ = " << static_ << std::endl;
    return static_++;
}

int main(int argc, char **argv) {
    ASSERT(func(5) == 5, "static variable value incorrect");
    ASSERT(func(4) == 6, "static variable value incorrect");
    ASSERT(func(3) == 7, "static variable value incorrect");
    ASSERT(func(2) == 8, "static variable value incorrect");
    ASSERT(func(1) == 9, "static variable value incorrect");
    return 0;
}
