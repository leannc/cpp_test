//
// Created by kang on 2024/11/9.
//

#include "ShapeModel.h"

/**
 * 这个模式中，主要是把Circle和Square的继承关系剥离出来了，但是加operation还是很麻烦，加operation的步骤为：
 * 1. ShapeConcept里面添加一个纯虚的operation
 * 2. ShapeModel在继承的时候，需要实现这个纯虚的operation
 * 3. 在ShapeModel实现operation的时候，有几种方式实现这个：
 *         (drawe函数)a.
 * 改变ShapeModel的签名，再传入一个std::function，由这个std::function的成员变量，去完成具体的operation。这样动静很大，因为所有实例化ShapeModel的地方，都需要改
 *        (origin函数)b.
 * 在concept里面，为新增的operation添一个参数，要求一个实现的函数，然后给个默认值，这样改动也比较小，只需要在model里面delegate一下就可以了，这样不关系的类，就用默认的函数，关心的类，自己写实现。
 *          (area函数)c.
 * 直接调用ShapeT的成员函数，这样就会导致ShapeT再也不是简单的数据结构，而且跟普通的inheritance的工作量差不多。
 *    ★(perimeter函数)d. 利用模板特化的方式，在ShapModel里面直接定义
 * */

struct Circle {
  double radius;
  double center;
  double area() const { return radius * radius * 3.14; }
};

struct Square {
  double side;
  double center;
  double area() const { return side * side; }
};

template <typename T>
void draw(T const &);

/// 这里只能用模板特化，不能用同名的draw函数重载，因为在底下将draw作为参数输入的时候，会导致不知道输入的是哪个draw，它没有签名
template <>
void draw<Circle>(Circle const &circle) {
  std::cout << "the circle's radius is " << circle.radius << std::endl;
}

template <>
void draw<Square>(Square const &square) {
  std::cout << "the square's side is " << square.side << std::endl;
}

template <>
double perimeter<Circle>(Circle c) {
  return 2 * c.radius * 3.14;
}

template <>
double perimeter<Square>(Square s) {
  return 4 * s.side;
}

void external_polymorphism_pattern() {
  std::unique_ptr<ShapeConcept> circle_1 = std::make_unique<ShapeModel<Circle>>(Circle(10, 11), draw<Circle>);
  std::unique_ptr<ShapeConcept> square_1 = std::make_unique<ShapeModel<Square>>(Square(3, 4), draw<Square>);

  circle_1->draw();
  square_1->draw();

  std::cout << "the area of circle is " << circle_1->area() << std::endl;
  std::cout << "the area of square is " << square_1->area() << std::endl;

  std::cout << "the perimeter of circle is " << circle_1->perimeter() << std::endl;
  std::cout << "the perimeter of square is " << square_1->perimeter() << std::endl;

  std::cout << "the origin of circle is " << circle_1->origin() << std::endl;
  std::cout << "the origin of square is " << square_1->origin() << std::endl;

  std::cout << "the edited origin of circle is " << circle_1->origin([]() { return 75.6; }) << std::endl;
}
