#pragma once
#include <entt.hpp>

#include <cereal/archives/binary.hpp>
#include <cereal/types/vector.hpp>

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

// 定义 ComplicateData 结构体，使用 std::shared_ptr<Position>
struct ComplicateData {
  std::vector<std::shared_ptr<Position>> positions_;
  std::unique_ptr<Position> my_position_;

  // 为 ComplicateData 结构体实现 serialize 函数
  template <class Archive>
  void serialize(Archive& archive) {
    archive(positions_, my_position_);
  }
};
