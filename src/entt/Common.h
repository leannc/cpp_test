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

  // 默认构造函数
  ComplicateData() = default;
  ~ComplicateData() = default;
  // 移动构造函数
  ComplicateData(ComplicateData&& other) noexcept = default;
  ComplicateData& operator=(const ComplicateData& other) = default;
  ComplicateData& operator=(ComplicateData&& other) noexcept = default;

  // 拷贝构造函数
  ComplicateData(const ComplicateData& other) {
    std::cout << "Copy constructor called for ComplicateData" << std::endl;
    for (const auto& posPtr : other.positions_) {
      positions_.push_back(std::make_shared<Position>(*posPtr));
    }
    if (other.my_position_) {
      my_position_ = std::make_unique<Position>(*other.my_position_);
    }
  }
};

struct LessComplicateData {
  std::vector<Position> positions_;

  // 为 ComplicateData 结构体实现 serialize 函数
  template <class Archive>
  void serialize(Archive& archive) {
    archive(positions_);
  }
};
