//
// Created by kang on 2024/12/16.
//

#include "UseCase.h"

class Circle {
 public:
  void draw() const { std::cout << "circle" << std::endl; }
};

class Box {
 public:
  void draw() { std::cout << "box" << std::endl; }
};

class Square {
 public:
  void draw() const { std::cout << "square" << std::endl; }
};

template <typename... Devs>
class ShapeBase {
 public:
  using Shapes = std::vector<std::variant<Devs...>>;
  explicit ShapeBase(Shapes shapes) : shapes_{std::move(shapes)} {}
  void draw() {
    for (auto& shape : shapes_) {
      std::visit([](auto& dev) { dev.draw(); }, shape);
    }
  }

 private:
  Shapes shapes_;
};

void std_variant_with_template() {
  ShapeBase<Circle, Square, Box> base{{Circle{}, Square{}, Box{}}};
  base.draw();
}
