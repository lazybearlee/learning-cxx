#include "../exercise.h"
#include <memory>

// READ: `std::shared_ptr` <https://zh.cppreference.com/w/cpp/memory/shared_ptr>
// READ: `std::weak_ptr` <https://zh.cppreference.com/w/cpp/memory/weak_ptr>

// TODO: 将下列 `?` 替换为正确的值
int main(int argc, char **argv) {
    auto shared = std::make_shared<int>(10);
    std::shared_ptr<int> ptrs[]{shared, shared, shared};

    std::weak_ptr<int> observer = shared;
    ASSERT(observer.use_count() == 4, "");

    ptrs[0].reset();
    ASSERT(observer.use_count() == 3, "");

    ptrs[1] = nullptr;
    ASSERT(observer.use_count() == 2, "");

    ptrs[2] = std::make_shared<int>(*shared);
    ASSERT(observer.use_count() == 1, "");

    ptrs[0] = shared;
    ptrs[1] = shared;
    ptrs[2] = std::move(shared);
    ASSERT(observer.use_count() == 3, ""); // shared 已经被移动，引用计数不会增加

    std::ignore = std::move(ptrs[0]); // 移动 ptrs[0]，但是不改变引用计数
    // std::ignore 是标准库里的一个特殊对象，它的赋值运算符（operator=）通常定义为接收一个“任意类型的常引用”（const T&）。
    // 虽然写了 std::move(ptrs[0])（把它转成了右值引用），但它最终还是匹配到了 std::ignore 的 const T& 接口。
    // 由于没有发生真正的“移动构造”或“移动赋值”给另一个智能指针，ptrs[0] 内部的指针并没有被置空。
    // 所以，这一行其实是个无效操作。
    ptrs[1] = std::move(ptrs[1]); 
    ptrs[1] = std::move(ptrs[2]); 
    ASSERT(observer.use_count() == 2, "");

    shared = observer.lock();
    ASSERT(observer.use_count() == 3, "");

    shared = nullptr;
    for (auto &ptr : ptrs) ptr = nullptr;
    ASSERT(observer.use_count() == 0, "");
    shared = observer.lock();
    ASSERT(observer.use_count() == 0, ""); // 资源已经被释放，无法 lock 到有效的 shared_ptr

    return 0;
}
