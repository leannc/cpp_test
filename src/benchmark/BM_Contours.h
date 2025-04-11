#pragma once
#include <random>

#include <entt.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Point {
  double x;
  double y;
};

struct Contour {
  std::vector<Point> points;

  Contour() = default;
  // 生成指定数量的随机点
  Contour(size_t num_points, std::mt19937& rng) {  // NOLINT
    std::uniform_real_distribution<double> dist(-100.0, 100.0);
    points.reserve(num_points);
    for (size_t i = 0; i < num_points; ++i) {
      points.push_back({dist(rng), dist(rng)});
    }
  }
};

struct CAMContour {
  Contour origin_contour;

  int noisy_item_1;
  float noisy_item_2;
  double noisy_item_3;
  bool noisy_item_4;
  // std::vector<std::unique_ptr<Contour>> cam_operations;
  std::vector<Contour> cam_operations;

  CAMContour(size_t num_points, size_t num_operations, std::mt19937& rng) : origin_contour(num_points, rng) {  // NOLINT
    std::uniform_int_distribution<int> dist(0, 100);
    noisy_item_1 = dist(rng);
    noisy_item_2 = dist(rng);
    noisy_item_3 = dist(rng);
    noisy_item_4 = dist(rng) % 2 == 0;

    origin_contour = Contour(num_points, rng);
    cam_operations.reserve(num_operations);
    for (size_t i = 0; i < num_operations; ++i) {
      // cam_operations.emplace_back(std::make_unique<Contour>(num_points, rng));
      cam_operations.emplace_back(num_points, rng);
    }
  }

  void traverse(size_t& sum) {
    for (const auto& point : origin_contour.points) {
      // sum += sqrt(point.x * point.x)  - sqrt(point.y * point.y);  // cppcheck-suppress unreadVariable
      sum += point.x;
      // sum++;
      // benchmark::DoNotOptimize(point);
    }

    for (const auto& contour : cam_operations) {
      for (const auto& point : contour.points) {
        // sum += sqrt(point.x * point.x)  - sqrt(point.y * point.y);  // cppcheck-suppress unreadVariable
        sum++;
        // benchmark::DoNotOptimize(point);
      }
    }
  }
};

struct ContourComponent {
  Contour contour;

  ContourComponent(size_t num_points, std::mt19937& rng) { contour = Contour(num_points, rng); }
};

struct MicroLinkCam1 {
  int noisy_item_1;
  float noisy_item_2;
  double noisy_item_3;
  bool noisy_item_4;
  std::vector<Contour> contours;

  MicroLinkCam1(size_t num_points, std::mt19937& rng) { contours.emplace_back(num_points, rng); }
};

struct MicroLinkCam2 {
  int noisy_item_1;
  float noisy_item_2;
  double noisy_item_3;
  bool noisy_item_4;
  std::vector<Contour> contours;

  MicroLinkCam2(size_t num_points, std::mt19937& rng) { contours.emplace_back(num_points, rng); }
};

struct MicroLinkCam3 {
  int noisy_item_1;
  float noisy_item_2;
  double noisy_item_3;
  bool noisy_item_4;
  std::vector<Contour> contours;

  MicroLinkCam3(size_t num_points, std::mt19937& rng) { contours.emplace_back(num_points, rng); }
};

struct MicroLinkCam4 {
  int noisy_item_1;
  float noisy_item_2;
  double noisy_item_3;
  bool noisy_item_4;
  std::vector<Contour> contours;

  MicroLinkCam4(size_t num_points, std::mt19937& rng) { contours.emplace_back(num_points, rng); }
};

struct MicroLinkCam5 {
  int noisy_item_1;
  float noisy_item_2;
  double noisy_item_3;
  bool noisy_item_4;
  std::vector<Contour> contours;

  MicroLinkCam5(size_t num_points, std::mt19937& rng) { contours.emplace_back(num_points, rng); }
};

struct MicroLinkCam6 {
  int noisy_item_1;
  float noisy_item_2;
  double noisy_item_3;
  bool noisy_item_4;
  std::vector<Contour> contours;

  MicroLinkCam6(size_t num_points, std::mt19937& rng) { contours.emplace_back(num_points, rng); }
};

struct MicroLinkCam7 {
  int noisy_item_1;
  float noisy_item_2;
  double noisy_item_3;
  bool noisy_item_4;
  std::vector<Contour> contours;

  MicroLinkCam7(size_t num_points, std::mt19937& rng) { contours.emplace_back(num_points, rng); }
};

struct MicroLinkCam8 {
  int noisy_item_1;
  float noisy_item_2;
  double noisy_item_3;
  bool noisy_item_4;
  std::vector<Contour> contours;

  MicroLinkCam8(size_t num_points, std::mt19937& rng) { contours.emplace_back(num_points, rng); }
};

struct MicroLinkCam9 {
  int noisy_item_1;
  float noisy_item_2;
  double noisy_item_3;
  bool noisy_item_4;
  std::vector<Contour> contours;

  MicroLinkCam9(size_t num_points, std::mt19937& rng) { contours.emplace_back(num_points, rng); }
};

struct MicroLinkCam10 {
  int noisy_item_1;
  float noisy_item_2;
  double noisy_item_3;
  bool noisy_item_4;
  std::vector<Contour> contours;

  MicroLinkCam10(size_t num_points, std::mt19937& rng) { contours.emplace_back(num_points, rng); }
};

struct ECSDocument {
  // entt::registry registry;
  // using entity_type = entt::basic_entity<std::uint64_t>;
  entt::basic_registry<std::uint32_t> registry;

  ECSDocument(size_t num_contours, size_t num_points, size_t num_operations) {
    std::random_device rd;
    std::mt19937 rng(rd());
    for (size_t i = 0; i < num_contours; i += 2) {
      auto entity = registry.create();
      registry.emplace<ContourComponent>(entity, num_points, rng);
      registry.emplace<MicroLinkCam1>(entity, num_points, rng);
      registry.emplace<MicroLinkCam2>(entity, num_points, rng);
      registry.emplace<MicroLinkCam3>(entity, num_points, rng);
      registry.emplace<MicroLinkCam4>(entity, num_points, rng);
      registry.emplace<MicroLinkCam5>(entity, num_points, rng);
      registry.emplace<MicroLinkCam6>(entity, num_points, rng);
      registry.emplace<MicroLinkCam7>(entity, num_points, rng);
      registry.emplace<MicroLinkCam8>(entity, num_points, rng);
      registry.emplace<MicroLinkCam9>(entity, num_points, rng);
      registry.emplace<MicroLinkCam10>(entity, num_points, rng);
    }
  }
};

template <typename Component>
void CAMTraversalSystem(entt::basic_registry<std::uint32_t>& registry, double& sum) {
  auto view = registry.view<Component>();
  for (auto entity : view) {
    auto& cam_component = view.get<Component>(entity);
    for (const auto& contour : cam_component.contours) {
      for (const auto& point : contour.points) {
        // auto pt = transformMatrix * glm::vec3(point.x, point.y, 1.0f);
        // sum += pt.x;
        sum += point.x;
      }
    }
  }
}
