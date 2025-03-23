//
// Created by kang on 2024/11/3.
//
#include "UseCase.h"

#include <array>
#include <list>
#include <span>
#include <stack>

void print(std::span<int> s) {
  std::for_each(s.begin(), s.end(), [](int element) { std::cout << element << ","; });
  *s.begin() = 999;
  std::cout << std::endl;
}

void std_span() {
  //    std::stack<int,std::vector<int>> s;
  std::vector<int> v{1, 2, 3, 4, 5, 6};
  std::cout << "----------std::vector---------" << std::endl;
  print(v);
  print(v);

  std::array<int, 3> arr = {10, 20, 30};
  std::cout << "----------std::array---------" << std::endl;
  print(arr);

  int raw_array[3] = {110, 210, 310};
  std::cout << "----------raw array---------" << std::endl;
  print(raw_array);

  std::list<int> list = {101, 201, 301};
  std::cout << "----------std::list---------" << std::endl;
  //    print(list);   ///报错，span不能代表list

  std::span s = v;  /// 这个地方非常cheap，因为s就只是一个 指针+长度 而已
  std::cout << "----------std span---------" << std::endl;
  print(s);
  std::cout << s.size() << std::endl;
}
