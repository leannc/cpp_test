//
// Created by kang on 2024/10/10.
//
#include "UseCase.h"

/**
 * NOTE:当参数包(parameter pack)是在函数的参数列表内部展开时，就不用折叠表达式(fold expression)，直接写patern...就可以
 * NOTE:当参数包的展开，是要加上整个函数表达时，就需要用折叠表达式，例如逗号表达式等来处理。
 */

void process(int &&i, const std::string &s) { std::cout << "Processing: " << i << ", " << s << std::endl; }

// NOTE:在函数的参数列表里面直接使用args参数包时，就不需要逗号，直接可以进行包展开，这里的pattern是std::forward<Args>(args)
template <typename... Args>
void perfect_forwading(Args &&...args) {
  process(std::forward<Args>(args)...);
}

template <typename T>
void print(T &&t) {
  std::cout << t << " --END";
}

template <typename T, typename... Args>
void print(T &&t, Args &&...args) {
  std::cout << t << " ";
  print(std::forward<Args>(args)...);
}

void parameter_pack_expansion_and_perfect_forwarding() {
  int x = 42;
  std::string str = "Hello, World!";
  perfect_forwading(10, str);            // 传递右值和左值
  perfect_forwading(std::move(x), str);  // 传递右值和左值

  print(1, 2.5, "Hello", 'A');
}
