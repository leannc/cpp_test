#pragma once
#include <entt.hpp>

struct Position {
  int x, y;
};

struct Velocity {
  int dx, dy;
};

struct Acceleration {
  int ax, ay;
};

class Document {
 public:
  entt::registry registry_;
};
