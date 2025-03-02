//
// Created by kang on 2024/12/1.
//

/**
 * declval可以假装构造了某一个类型，进而在不需要construct的情况下，实现
 * */
#include "UseCase.h"

template <typename T>
struct Point {
  T x;
  T y;
  T center();
};

template <typename T>
int only_declaration_function(Point<T>);

template <typename T>
void type_assert() {
  static_assert(std::is_same_v<int, decltype(only_declaration_function(std::declval<Point<T>>()))>);
  std::cout << "all done" << std::endl;
}

template <typename T, typename = int>
struct has_center : std::false_type {};

template <typename T>
struct has_center<T, decltype(std::declval<T>().center(), 0)> : std::true_type {};

void std_declval() {
  type_assert<int>();
  std::cout << has_center<Point<double>>::value << std::endl;
  std::cout << has_center<int>::value << std::endl;
}
