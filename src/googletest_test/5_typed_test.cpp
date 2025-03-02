#include "UseCase.h"

// 还有一个 parameterized的版本，没有写，可以不需要提前指定子类型

class Shape {
 public:
  virtual void draw() const = 0;
};

class Circle : public Shape {
 public:
  void draw() const override { std::cout << "Circle" << std::endl; }
};

class Rectangle : public Shape {
 public:
  void draw() const override { std::cout << "Rectangle" << std::endl; }
};

template <typename T>
class TypedTestSuite : public ::testing::Test {
 public:
  T shape_;
};

typedef ::testing::Types<Circle, Rectangle> Implementations;
TYPED_TEST_SUITE(TypedTestSuite, Implementations);

TYPED_TEST(TypedTestSuite, Draw) { this->shape_.draw(); }
