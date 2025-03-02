//
// Created by kang on 2024/11/9.
//

#include "Shape.h"

/**
 *
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

void owning_type_erasure_implementation() {
  Circle circle_1{3.12};

  auto drawer = [](Circle const &c) {
    std::cout << "draw circle,radius is " << c.radius << std::endl;
  };

  Shape shape1(circle_1, drawer);
  //    draw(shape1);
  shape1.draw();
}
