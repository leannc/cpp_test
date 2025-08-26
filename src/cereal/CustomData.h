#pragma once

#define CEREAL_SERIALIZE(...)                                                                                          \
  template <class Archive>                                                                                             \
  void serialize(Archive& archive) {                                                                                   \
    archive(__VA_ARGS__);                                                                                              \
  }

namespace cereal_test {
struct Point {
  int x, y;

  CEREAL_SERIALIZE(x, y);
};

struct Polygon {
  std::vector<Point> points;

  CEREAL_SERIALIZE(points);
};

struct Polygons {
  std::vector<Polygon> polygons;

  CEREAL_SERIALIZE(polygons);
};

struct Scene {
  std::vector<Polygon> elements;
  std::unordered_map<std::string, Polygon> polygons_map;
  std::unordered_map<std::string, std::unique_ptr<Point>> points_map;

  CEREAL_SERIALIZE(elements, polygons_map, points_map);
};

}  // namespace cereal_test
