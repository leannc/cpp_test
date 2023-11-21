//
// Created by wangkang on 2023/11/20.
//
#include <iostream>

// 定义一个占位符类型，用于表示调用者的类型
struct CallerTypePlaceholder
        {
    void print()
    {
        std::cout << "CallerTypePlaceholder" << std::endl;
    }
        };

// 定义一个带有模板参数的函数模板，使用 decltype 推导调用者的类型
template <typename T = CallerTypePlaceholder>
void GetCallerType(T&& caller = CallerTypePlaceholder{}) {
    // 使用 decltype 获取调用者的类型
    using CallerType = typename std::remove_reference<T>::type;
//    using CallerType = decltype(caller);

    CallerType caller2;
    caller2.print();


    // 打印调用者的类型
    std::cout << "Caller Type: " << typeid(CallerType).name() << std::endl;

}

// 示例使用
struct ExampleCaller
        {
        void print()
        {
            std::cout << "ExampleCaller" << std::endl;
        }

        };

int main() {
    // 在 main 函数中调用 GetCallerType
    GetCallerType(); // 调用者类型是 CallerTypePlaceholder
    GetCallerType(ExampleCaller()); // 调用者类型是 ExampleCaller

    return 0;
}
