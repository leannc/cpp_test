//
// Created by kang on 2023/11/21.
//

#include "UseCase.h"

void std_variant_with_visitor() {
  std::variant<int, double, std::string> v = "hello";
  std::visit(
      [](auto &&arg) {
        using T = std::decay_t<decltype(arg)>;
        if constexpr (std::is_same_v<T, int>) {
          std::cout << "int:{}" << arg << std::endl;
        } else if constexpr (std::is_same_v<T, double>) {
          std::cout << "double:{}" << arg << std::endl;
        } else if constexpr (std::is_same_v<T, std::string>) {
          std::cout << "string:{}" << arg << std::endl;
        }
      },
      v);

  auto func = [](auto x) { std::cout << x << std::endl; };

  func("abc");
  func(123);
  func(45.67);
}

template <class... Ts> struct overloaded : Ts... {
  using Ts::operator()...;
};
// explicit deduction guide (not needed as of C++20)
template <class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

void std_variant_with_visitor2() {
  std::vector<std::variant<int, double, std::string>> variant_list = {
      "hello", 20, 31.23, "kang"};

  for (auto &variant : variant_list) {
    /// 这里用std::visit来写
    std::visit(
        overloaded{[](auto arg) {
                     std::cout << "the default value is " << arg << std::endl;
                   },
                   [](double arg) {
                     std::cout << "the double value is " << arg << std::endl;
                   },
                   [](std::string arg) {
                     std::cout << "the string value is " << arg << std::endl;
                   }},
        variant);
  }
}

//------------------------------powerful--------------------------------
class Circle {
 public:
  void DrawCircle() const { std::cout << "circle" << std::endl; }
};

class Box {
 public:
  void DrawBox() const { std::cout << "box" << std::endl; }
};

class Square {
 public:
  void DrawSquare() const { std::cout << "square" << std::endl; }
};

class Draw {
 public:
  void operator()(Circle &c) { c.DrawCircle(); }
  void operator()(Box &b) { b.DrawBox(); }
  void operator()(Square &s) { s.DrawSquare(); }
};

using Shape = std::variant<Circle, Box, Square>;

void std_variant_with_visitor3() {
  std::vector<Shape> variant_list = {Circle{}, Box{}, Square{}};

  for (auto &variant : variant_list) {
    /// 这里用std::visit来写
    std::visit(Draw{}, variant);
  }
}

//-------------------pointer version-------------------------------------
class Draw2 {
 public:
  void operator()(Circle *c) { c->DrawCircle(); }
  void operator()(Box *b) { b->DrawBox(); }
  void operator()(Square *s) { s->DrawSquare(); }
};

using ShapePointer = std::variant<Circle *, Box *, Square *>;

void std_variant_with_visitor4() {
  Circle c;
  Box b;
  Square s;
  std::vector<ShapePointer> variant_pointer_list = {&c, &b, &s};

  for (auto &variant : variant_pointer_list) {
    /// 这里用std::visit来写
    std::visit(Draw2{}, variant);
  }
}