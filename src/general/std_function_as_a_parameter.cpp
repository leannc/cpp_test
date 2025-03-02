//
// Created by kang on 2024/10/29.
//

#include "UseCase.h"

int demo_func_1(std::string s) {
  std::cout << "calling demo func 1 : " << s << std::endl;

  return 1;
}

void demo_function_call_without_para(int a, std::function<int(std::string)> f) {
  auto result = a + f("wang");
  std::cout << result << std::endl;
}

int demo_func_2(std::string s, int b) {
  std::cout << "calling demo func 1 : " << s << std::endl;

  return b;
}

void std_function_as_a_parameter_test() {
  std::function<int(std::string)> f;

  f = demo_func_1;
  demo_function_call_without_para(4, f);

  f = std::bind(demo_func_2, std::placeholders::_1, 7);
  demo_function_call_without_para(4, f);

  demo_function_call_without_para(17, [](std::string s) {
    std::cout << "in lambda function" << std::endl;
    return 31;
  });
}
