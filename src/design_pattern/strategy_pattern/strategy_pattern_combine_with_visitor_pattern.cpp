//
// Created by kang on 2023/11/21.
//

#include "../UseCase.h"

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

class Other {
 public:
  void DrawOther() const { std::cout << "other" << std::endl; }
};

class Other2 {
 public:
  void DrawOther() const { std::cout << "other2" << std::endl; }
};

class StrategyDraw {
 public:
  StrategyDraw(std::string s) { strategy = s; }

 public:
  void operator()(Circle &c) {
    c.DrawCircle();
    std::cout << strategy << std::endl;
  }
  void operator()(Box &b) {
    b.DrawBox();
    std::cout << strategy << std::endl;
  }
  void operator()(Square &s) {
    s.DrawSquare();
    std::cout << strategy << std::endl;
  }
  void operator()(auto &s) {
    s.DrawOther();
    std::cout << strategy << std::endl;
  }  // 默认参数，如果没有匹配的，就调用这个

 private:
  std::string strategy;
};

using Shape = std::variant<Circle, Box, Square, Other, Other2>;

void strategy_pattern_combine_with_visitor_pattern() {
  std::vector<Shape> variant_list = {Circle{}, Other2{}, Box{}, Square{}, Other{}};

  for (auto &variant : variant_list) {
    /// 这里用std::visit来写
    std::visit(StrategyDraw{"opengl"}, variant);
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

void visitor_pattern_in_std_variant_form_pointer_version_22() {
  Circle c;
  Box b;
  Square s;
  std::vector<ShapePointer> variant_pointer_list = {&c, &b, &s};

  for (auto &variant : variant_pointer_list) {
    /// 这里用std::visit来写
    std::visit(Draw2{}, variant);
  }
}
