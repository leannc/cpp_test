#pragma once
#include <entt.hpp>

struct Position {
  float x, y;

  // 模板函数，用于序列化和反序列化Position对象
  template <class Archive>
  void serialize(Archive& archive) {
    archive(x, y);
  }
};

struct Velocity {
  float dx, dy;

  template <class Archive>
  void serialize(Archive& archive) {
    archive(dx, dy);
  }
};

struct Acceleration {
  float ax, ay;
};

class Document {
 public:
  entt::registry registry_;
};
