//
// Created by kang on 2024/11/2.
//
#include "../UseCase.h"

template <typename DrawStrategy>
class Circle {
 public:
  Circle(double radius_, DrawStrategy drawer_) : radius(radius_), drawer(drawer_) {}

  void draw() { drawer.draw(); }

 private:
  double radius;
  DrawStrategy drawer;
};

class OpenglDrawer {
 public:
  void draw() { std::cout << "using opengl drawer" << std::endl; }
};

class MetalDrawer {
 public:
  int draw() {
    std::cout << "using metal drawer" << std::endl;
    return 3;
  }
};

void strategy_using_template_params() {
  OpenglDrawer opengl_drawer;
  MetalDrawer metal_drawer;

  Circle c1(2.34, opengl_drawer);
  Circle c2(10, metal_drawer);

  c1.draw();
  c2.draw();
}
