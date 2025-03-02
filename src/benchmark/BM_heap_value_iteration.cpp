#include "UseCase.h"
#include <execution>
#include <immintrin.h>  // AVX SIMD
#include <random>
#include <vector>

struct Point {
  double x;
  double y;
};

struct Contour {
  std::vector<Point> points;

  // 生成指定数量的随机点
  Contour(size_t num_points, std::mt19937 &rng) {  // NOLINT
    std::uniform_real_distribution<double> dist(-100.0, 100.0);
    points.reserve(num_points);
    for (size_t i = 0; i < num_points; ++i) {
      points.push_back({dist(rng), dist(rng)});
    }
  }
};

// 生成随机 Contour 数据
std::vector<std::unique_ptr<Contour>> generateContours(size_t num_contours, size_t min_points, size_t max_points) {
  std::vector<std::unique_ptr<Contour>> contours;
  contours.reserve(num_contours);

  std::random_device rd;
  std::mt19937 rng(rd());
  std::uniform_int_distribution<size_t> point_dist(min_points, max_points);

  for (size_t i = 0; i < num_contours; ++i) {
    contours.push_back(std::make_unique<Contour>(point_dist(rng), rng));
  }

  return contours;
}

// 生成随机数的辅助函数
int getRandomInt(int min, int max) {
  static std::random_device rd;
  static std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(min, max);
  return dis(gen);
}

// **基准测试 1：使用 `vector<vector<double>>`**
void BM_HeapContourPoint_traversal(benchmark::State &state) {  // NOLINT
  int minPoints = state.range(0);
  int maxPoints = state.range(1);
  int numContours = state.range(2);

  auto n_contour = getRandomInt(numContours - 5, numContours + 5);
  // 在堆上构造 Contour 对象
  auto contours = generateContours(n_contour, minPoints, maxPoints);

  // 计算总点数
  size_t total_points = 0;
  for (const auto &contour : contours) {
    total_points += contour->points.size();
  }

  size_t total = 0;
  for (auto _ : state) {
    // 遍历所有 Contour 中的点
    double sum = 0.0;
    for (const auto &contour : contours) {
      for (const auto &point : contour->points) {
        // sum += sqrt(point.x * point.x)  - sqrt(point.y * point.y);  // cppcheck-suppress unreadVariable
        sum += point.x + point.y;
        // benchmark::DoNotOptimize(point);
      }
    }
    total += sum;
    // benchmark::DoNotOptimize(sum);
    // benchmark::ClobberMemory();
  }
  std::cout << "the total is " << total << std::endl;
  // 确保统计的是遍历的点数，而不是 contours 数量
  //   state.SetItemsProcessed(contours.size() * state.iterations());
}

void BM_HeapContourPoint_traversal_parallel(benchmark::State &state) {  // NOLINT
  int minPoints = state.range(0);
  int maxPoints = state.range(1);
  int numContours = state.range(2);

  // 在堆上构造 Contour 对象
  auto contours = generateContours(numContours, minPoints, maxPoints);
  size_t total = 0;
  for (auto _ : state) {
    // 遍历所有 Contour 中的点
    double sum = 0.0;
    std::for_each(std::execution::par, contours.begin(), contours.end(), [&sum](const auto &contour) {
      for (const auto &point : contour->points) {
        // sum += sqrt(point.x * point.x)  - sqrt(point.y * point.y);  // cppcheck-suppress unreadVariable
        sum += point.x + point.y;
        // benchmark::DoNotOptimize(point);
      }
    });
    total += sum;
  }

  std::cout << "the parallel total is " << total << std::endl;
}
