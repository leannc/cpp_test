

#include "UseCase.h"

#include <immintrin.h>  // AVX SIMD
#include <plf_colony.h>

#include <execution>
#include <functional>
#include <random>
#include <vector>

#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index_container.hpp>

#include "BM_Contours.h"

// 旋转操作
// 旋转角度（弧度制），这里旋转 45 度
float rotationAngle = glm::radians(45.0f);
// 创建 2D 旋转矩阵
glm::mat3 rotationMatrix = glm::mat3(glm::cos(rotationAngle), -glm::sin(rotationAngle), 0.0f, glm::sin(rotationAngle),
                                     glm::cos(rotationAngle), 0.0f, 0.0f, 0.0f, 1.0f);

// 平移操作
// 平移向量
glm::vec2 translation(2.0f, 3.0f);
// 创建 2D 平移矩阵
glm::mat3 translationMatrix = glm::mat3(1.0f, 0.0f, translation.x, 0.0f, 1.0f, translation.y, 0.0f, 0.0f, 1.0f);

// 缩放操作
// 缩放因子
glm::vec2 scaleFactor(1.5f, 2.0f);
// 创建 2D 缩放矩阵
glm::mat3 scaleMatrix = glm::mat3(scaleFactor.x, 0.0f, 0.0f, 0.0f, scaleFactor.y, 0.0f, 0.0f, 0.0f, 1.0f);

// 组合变换矩阵，注意矩阵乘法顺序，这里是先旋转，再平移，最后缩放
glm::mat3 transformMatrix = scaleMatrix * translationMatrix * rotationMatrix;

// ----------------ECS的遍历---------------------------
void ContourTraversalSystem(entt::basic_registry<std::uint32_t>& registry, double& sum) {
  // 遍历所有 Contour 中的点
  auto view = registry.view<ContourComponent>();
  for (auto entity : view) {
    auto& contour = view.get<ContourComponent>(entity);
    for (const auto& point : contour.contour.points) {
      // sum += sqrt(point.x * point.x)  - sqrt(point.y * point.y);  // cppcheck-suppress unreadVariable
      sum += point.x;
      // auto pt = transformMatrix * glm::vec3(point.x, point.y, 1.0f);
      // sum += pt.x;
      // benchmark::DoNotOptimize(point);
    }
  }
}

// **基准测试 1：使用 `vector<vector<double>>`**
void BM_CAMContour_ECS_traversal(benchmark::State& state) {  // NOLINT
  int minPoints = state.range(0);
  int maxPoints = state.range(1);
  int numContours = state.range(2);

  std::random_device rd;
  std::mt19937 rng(rd());
  std::uniform_int_distribution<size_t> point_dist(minPoints, maxPoints);

  ECSDocument doc(numContours, point_dist(rng), 0);

  double total = 0;

  for (auto _ : state) {
    // std::vector<std::function<void(void)>> tasks;

    // tasks.emplace_back([&doc, &total]() { ContourTraversalSystem(doc.registry, total); });
    // tasks.emplace_back([&doc, &total]() { CAMTraversalSystem<MicroLinkCam1>(doc.registry, total); });
    // tasks.emplace_back([&doc, &total]() { CAMTraversalSystem<MicroLinkCam2>(doc.registry, total); });
    // tasks.emplace_back([&doc, &total]() { CAMTraversalSystem<MicroLinkCam3>(doc.registry, total); });
    // tasks.emplace_back([&doc, &total]() { CAMTraversalSystem<MicroLinkCam4>(doc.registry, total); });
    // tasks.emplace_back([&doc, &total]() { CAMTraversalSystem<MicroLinkCam5>(doc.registry, total); });
    // tasks.emplace_back([&doc, &total]() { CAMTraversalSystem<MicroLinkCam6>(doc.registry, total); });
    // tasks.emplace_back([&doc, &total]() { CAMTraversalSystem<MicroLinkCam7>(doc.registry, total); });
    // tasks.emplace_back([&doc, &total]() { CAMTraversalSystem<MicroLinkCam8>(doc.registry, total); });
    // tasks.emplace_back([&doc, &total]() { CAMTraversalSystem<MicroLinkCam9>(doc.registry, total); });
    // tasks.emplace_back([&doc, &total]() { CAMTraversalSystem<MicroLinkCam10>(doc.registry, total); });

    // std::for_each(std::execution::par, tasks.begin(), tasks.end(), [](auto& task) { task(); });

    // std::vector<std::thread> threads;
    // std::thread t0([&doc, &total]() { ContourTraversalSystem(doc.registry, total); });
    // std::thread t1([&doc, &total]() { CAMTraversalSystem<MicroLinkCam1>(doc.registry, total); });
    // std::thread t2([&doc, &total]() { CAMTraversalSystem<MicroLinkCam2>(doc.registry, total); });
    // std::thread t3([&doc, &total]() { CAMTraversalSystem<MicroLinkCam3>(doc.registry, total); });
    // std::thread t4([&doc, &total]() { CAMTraversalSystem<MicroLinkCam4>(doc.registry, total); });
    // std::thread t5([&doc, &total]() { CAMTraversalSystem<MicroLinkCam5>(doc.registry, total); });

    // // 等待所有线程完成
    // t0.join();
    // t1.join();
    // t2.join();
    // t3.join();
    // t4.join();
    // t5.join();

    ContourTraversalSystem(doc.registry, total);
    CAMTraversalSystem<MicroLinkCam1>(doc.registry, total);
    CAMTraversalSystem<MicroLinkCam2>(doc.registry, total);
    CAMTraversalSystem<MicroLinkCam3>(doc.registry, total);
    CAMTraversalSystem<MicroLinkCam4>(doc.registry, total);
    CAMTraversalSystem<MicroLinkCam5>(doc.registry, total);
    CAMTraversalSystem<MicroLinkCam6>(doc.registry, total);
    CAMTraversalSystem<MicroLinkCam7>(doc.registry, total);
    CAMTraversalSystem<MicroLinkCam8>(doc.registry, total);
    CAMTraversalSystem<MicroLinkCam9>(doc.registry, total);
    CAMTraversalSystem<MicroLinkCam10>(doc.registry, total);
  }
  // benchmark::DoNotOptimize(sum);
  // benchmark::ClobberMemory();
  std::cout << "the ecs total is " << total << std::endl;
}
// ----------------boost::multi_indexed_container的遍历---------------------------
// 定义 boost::multi_indexed_container 的标签
struct sequenced_tag {};

// 定义 boost::multi_indexed_container 类型
using CAMContourContainer =
    boost::multi_index::multi_index_container<CAMContour,
                                              boost::multi_index::indexed_by<boost::multi_index::sequenced<>>>;

// 生成随机 CAMContour 数据
CAMContourContainer generateBoostCAMContours(size_t num_contours, size_t min_points, size_t max_points) {
  CAMContourContainer contours;

  std::random_device rd;
  std::mt19937 rng(rd());
  std::uniform_int_distribution<size_t> point_dist(min_points, max_points);

  int cam_operation_num = 5;
  for (size_t i = 0; i < num_contours; ++i) {
    contours.emplace_back(point_dist(rng), cam_operation_num, rng);
  }

  return contours;
}

// **基准测试 1：使用 `vector<vector<double>>`**
void BM_CAMContour_Boost_Traditional_traversal(benchmark::State& state) {  // NOLINT
  int minPoints = state.range(0);
  int maxPoints = state.range(1);
  int numContours = state.range(2);

  // 在堆上构造 Contour 对象
  auto contours = generateBoostCAMContours(numContours, minPoints, maxPoints);

  // 计算总点数
  size_t total_points = 0;
  for (const auto& contour : contours) {
    total_points += contour.origin_contour.points.size();
  }

  size_t total = 0;
  for (auto _ : state) {
    // 遍历所有 Contour 中的点
    double sum = 0.0;
    for (const auto& contour : contours) {
      for (const auto& point : contour.origin_contour.points) {
        // sum += sqrt(point.x * point.x)  - sqrt(point.y * point.y);  // cppcheck-suppress unreadVariable
        sum++;
        // benchmark::DoNotOptimize(point);
      }

      for (const auto& cam_operation : contour.cam_operations) {
        // for (const auto& point : cam_operation->points) {
        for (const auto& point : cam_operation.points) {
          // sum += sqrt(point.x * point.x)  - sqrt(point.y * point.y);  // cppcheck-suppress unreadVariable
          sum++;
          // benchmark::DoNotOptimize(point);
        }
      }
    }
    total += sum;
    // benchmark::DoNotOptimize(sum);
    // benchmark::ClobberMemory();
  }
  std::cout << "the boost traditional total is " << total << std::endl;
  // 确保统计的是遍历的点数，而不是 contours 数量
  //   state.SetItemsProcessed(contours.size() * state.iterations());
}

// ----------------------unordered_map的遍历---------------------
std::unordered_map<size_t, CAMContour> generateUnorderedMapCAMContours(size_t num_contours, size_t min_points,
                                                                       size_t max_points) {
  std::unordered_map<size_t, CAMContour> contours;

  std::random_device rd;
  std::mt19937 rng(rd());
  std::uniform_int_distribution<size_t> point_dist(min_points, max_points);

  int cam_operation_num = 10;
  for (size_t i = 0; i < num_contours; ++i) {
    contours.emplace(i, CAMContour(point_dist(rng), cam_operation_num, rng));
  }

  return contours;
}

// **基准测试 1：使用 `vector<vector<double>>`**
void BM_CAMContour_Unordered_map_Traditional_traversal(benchmark::State& state) {  // NOLINT
  int minPoints = state.range(0);
  int maxPoints = state.range(1);
  int numContours = state.range(2);

  // 在堆上构造 Contour 对象
  auto contours = generateUnorderedMapCAMContours(numContours, minPoints, maxPoints);

  // 计算总点数
  size_t total_points = 0;
  for (const auto& [id, contour] : contours) {
    total_points += contour.origin_contour.points.size();
  }

  size_t total = 0;
  for (auto _ : state) {
    // 遍历所有 Contour 中的点
    double sum = 0.0;
    for (const auto& [id, contour] : contours) {
      for (const auto& point : contour.origin_contour.points) {
        // sum += sqrt(point.x * point.x)  - sqrt(point.y * point.y);  // cppcheck-suppress unreadVariable
        sum++;
        // benchmark::DoNotOptimize(point);
      }

      for (const auto& cam_operation : contour.cam_operations) {
        // for (const auto& point : cam_operation->points) {
        for (const auto& point : cam_operation.points) {
          // sum += sqrt(point.x * point.x)  - sqrt(point.y * point.y);  // cppcheck-suppress unreadVariable
          sum++;
          // benchmark::DoNotOptimize(point);
        }
      }
    }
    total += sum;
    // benchmark::DoNotOptimize(sum);
    // benchmark::ClobberMemory();
  }
  std::cout << "the unordered traditional total is " << total << std::endl;
  // 确保统计的是遍历的点数，而不是 contours 数量
  //   state.SetItemsProcessed(contours.size() * state.iterations());
}

// ----------------------plf::Colony的遍历---------------------
// 定义 plf 的标签
plf::colony<CAMContour> generatePlfCAMContours(size_t num_contours, size_t min_points, size_t max_points) {
  plf::colony<CAMContour> contours;

  std::random_device rd;
  std::mt19937 rng(rd());
  std::uniform_int_distribution<size_t> point_dist(min_points, max_points);

  int cam_operation_num = 10;
  for (size_t i = 0; i < num_contours; ++i) {
    contours.emplace(CAMContour(point_dist(rng), cam_operation_num, rng));
  }

  return contours;
}

// **基准测试 1：使用 `vector<vector<double>>`**
void BM_CAMContour_plf_colony_Traditional_traversal(benchmark::State& state) {  // NOLINT
  int minPoints = state.range(0);
  int maxPoints = state.range(1);
  int numContours = state.range(2);

  // 在堆上构造 Contour 对象
  auto contours = generatePlfCAMContours(numContours, minPoints, maxPoints);

  // 计算总点数
  size_t total_points = 0;
  for (const auto& contour : contours) {
    total_points += contour.origin_contour.points.size();
  }

  size_t total = 0;
  for (auto _ : state) {
    // 遍历所有 Contour 中的点
    double sum = 0.0;
    for (const auto& contour : contours) {
      for (const auto& point : contour.origin_contour.points) {
        // sum += sqrt(point.x * point.x)  - sqrt(point.y * point.y);  // cppcheck-suppress unreadVariable
        sum += point.x;
        // benchmark::DoNotOptimize(point);
      }

      for (const auto& cam_operation : contour.cam_operations) {
        // for (const auto& point : cam_operation->points) {
        for (const auto& point : cam_operation.points) {
          // sum += sqrt(point.x * point.x)  - sqrt(point.y * point.y);  // cppcheck-suppress unreadVariable
          sum += point.x;
          // benchmark::DoNotOptimize(point);
        }
      }
    }
    total += sum;
    // benchmark::DoNotOptimize(sum);
    // benchmark::ClobberMemory();
  }
  std::cout << "the plf total is " << total << std::endl;
  // 确保统计的是遍历的点数，而不是 contours 数量
  //   state.SetItemsProcessed(contours.size() * state.iterations());
}

// ---------------------传统的遍历----------------------

// 生成随机 CAMContour 数据
std::vector<CAMContour> generateCAMContours(size_t num_contours, size_t min_points, size_t max_points) {
  std::vector<CAMContour> contours;
  contours.reserve(num_contours);

  std::random_device rd;
  std::mt19937 rng(rd());
  std::uniform_int_distribution<size_t> point_dist(min_points, max_points);
  // std::uniform_int_distribution<size_t> cam_operations_dist(8, 10);  // 一共8-10个CAM操作：微联，冷却点等。

  int cam_operation_num = 10;
  for (size_t i = 0; i < num_contours; ++i) {
    contours.emplace_back(point_dist(rng), cam_operation_num, rng);
  }

  return contours;
}

// **基准测试 1：使用 `vector<vector<double>>`**
void BM_CAMContour_Traditional_traversal(benchmark::State& state) {  // NOLINT
  int minPoints = state.range(0);
  int maxPoints = state.range(1);
  int numContours = state.range(2);

  // 在堆上构造 Contour 对象
  auto contours = generateCAMContours(numContours, minPoints, maxPoints);

  // 计算总点数
  size_t total_points = 0;
  for (const auto& contour : contours) {
    total_points += contour.origin_contour.points.size();
  }

  size_t total = 0;
  for (auto _ : state) {
    // 遍历所有 Contour 中的点
    double sum = 0.0;
    // -------- 单线程版本 --------
    for (const auto& contour : contours) {
      for (const auto& point : contour.origin_contour.points) {
        // sum += sqrt(point.x * point.x)  - sqrt(point.y * point.y);  // cppcheck-suppress unreadVariable
        sum += point.x;
        // benchmark::DoNotOptimize(point);
      }

      for (const auto& cam_operation : contour.cam_operations) {
        // for (const auto& point : cam_operation->points) {
        for (const auto& point : cam_operation.points) {
          // sum += sqrt(point.x * point.x)  - sqrt(point.y * point.y);  // cppcheck-suppress unreadVariable
          sum += point.x;
          // benchmark::DoNotOptimize(point);
        }
      }
    }

    total += sum;
    // benchmark::DoNotOptimize(sum);
    // benchmark::ClobberMemory();
  }
  std::cout << "the traditional total is " << total << std::endl;
  // 确保统计的是遍历的点数，而不是 contours 数量
  //   state.SetItemsProcessed(contours.size() * state.iterations());
}

void BM_CAMContour_Traditional_multithread_traversal(benchmark::State& state) {  // NOLINT
  int minPoints = state.range(0);
  int maxPoints = state.range(1);
  int numContours = state.range(2);

  // 在堆上构造 Contour 对象
  auto contours = generateCAMContours(numContours, minPoints, maxPoints);

  // 计算总点数
  size_t total_points = 0;
  for (const auto& contour : contours) {
    total_points += contour.origin_contour.points.size();
  }

  size_t total = 0;
  for (auto _ : state) {
    // 遍历所有 Contour 中的点
    double sum = 0.0;
    // -------- 多线程版本 ---------
    std::for_each(std::execution::par, contours.begin(), contours.end(), [&sum](const auto& contour) {
      for (const auto& point : contour.origin_contour.points) {
        // sum += sqrt(point.x * point.x)  - sqrt(point.y * point.y);  // cppcheck-suppress unreadVariable
        sum += point.x;
        // benchmark::DoNotOptimize(point);
      }

      for (const auto& cam_operation : contour.cam_operations) {
        // for (const auto& point : cam_operation->points) {
        for (const auto& point : cam_operation.points) {
          // sum += sqrt(point.x * point.x)  - sqrt(point.y * point.y);  // cppcheck-suppress unreadVariable
          sum += point.x;
          // benchmark::DoNotOptimize(point);
        }
      }
    });

    total += sum;
    // benchmark::DoNotOptimize(sum);
    // benchmark::ClobberMemory();
  }
  std::cout << "the traditional total is " << total << std::endl;
  // 确保统计的是遍历的点数，而不是 contours 数量
  //   state.SetItemsProcessed(contours.size() * state.iterations());
}

// ---------------------只有contour的遍历----------------------

// 生成随机 CAMContour 数据
std::vector<CAMContour> generatePureContours(size_t num_contours, size_t min_points, size_t max_points) {
  std::vector<CAMContour> contours;
  contours.reserve(num_contours);

  std::random_device rd;
  std::mt19937 rng(rd());
  std::uniform_int_distribution<size_t> point_dist(min_points, max_points);
  // std::uniform_int_distribution<size_t> cam_operations_dist(8, 10);  // 一共8-10个CAM操作：微联，冷却点等。

  int cam_operation_num = 0;
  for (size_t i = 0; i < num_contours; ++i) {
    contours.emplace_back(point_dist(rng), cam_operation_num, rng);
  }

  return contours;
}

// **基准测试 1：使用 `vector<vector<double>>`**
void BM_CAMContour_pure_contour_Traditional_traversal(benchmark::State& state) {  // NOLINT
  int minPoints = state.range(0);
  int maxPoints = state.range(1);
  int numContours = state.range(2);

  // 在堆上构造 Contour 对象
  auto contours = generatePureContours(numContours, minPoints, maxPoints);
  std::unordered_map<int, std::vector<CAMContour>> cams;

  for (int i = 0; i < 10; i++) {
    cams[i] = generatePureContours(numContours, minPoints, maxPoints);
  }
  // 计算总点数
  size_t total_points = 0;
  for (const auto& contour : contours) {
    total_points += contour.origin_contour.points.size();
  }

  size_t total = 0;
  for (auto _ : state) {
    // 遍历所有 Contour 中的点
    double sum = 0.0;

    for (const auto& contour : contours) {
      for (const auto& point : contour.origin_contour.points) {
        // sum += sqrt(point.x * point.x)  - sqrt(point.y * point.y);  // cppcheck-suppress unreadVariable
        sum += point.x;
        // benchmark::DoNotOptimize(point);
      }
    }

    for (auto& [id, cam] : cams) {
      for (const auto& contour : cam) {
        for (const auto& point : contour.origin_contour.points) {
          // sum += sqrt(point.x * point.x)  - sqrt(point.y * point.y);  // cppcheck-suppress unreadVariable
          sum += point.x;
          // benchmark::DoNotOptimize(point);
        }
      }
    }

    total += sum;
    // benchmark::DoNotOptimize(sum);
    // benchmark::ClobberMemory();
  }
  std::cout << "the traditional total is " << total << std::endl;
  // 确保统计的是遍历的点数，而不是 contours 数量
  //   state.SetItemsProcessed(contours.size() * state.iterations());
}

// ---------------------transform的遍历----------------------
void BM_CAMContour_Traditional_transform_traversal(benchmark::State& state) {  // NOLINT
  int minPoints = state.range(0);
  int maxPoints = state.range(1);
  int numContours = state.range(2);

  // 在堆上构造 Contour 对象
  auto contours = generateCAMContours(numContours, minPoints, maxPoints);

  // 计算总点数
  size_t total_points = 0;
  for (const auto& contour : contours) {
    total_points += contour.origin_contour.points.size();
  }

  size_t total = 0;
  for (auto _ : state) {
    // 遍历所有 Contour 中的点
    double sum = 0.0;
    for (const auto& contour : contours) {
      for (const auto& point : contour.origin_contour.points) {
        // sum += sqrt(point.x * point.x)  - sqrt(point.y * point.y);  // cppcheck-suppress unreadVariable
        auto pt = transformMatrix * glm::vec3(point.x, point.y, 1.0f);
        sum += pt.x;
        // sum += point.x;
        // benchmark::DoNotOptimize(point);
      }

      for (const auto& cam_operation : contour.cam_operations) {
        // for (const auto& point : cam_operation->points) {
        for (const auto& point : cam_operation.points) {
          auto pt = transformMatrix * glm::vec3(point.x, point.y, 1.0f);
          sum += pt.x;
          // sum += point.x;
          // benchmark::DoNotOptimize(point);
        }

        for (const auto& cam_operation : contour.cam_operations) {
          // for (const auto& point : cam_operation->points) {
          for (const auto& point : cam_operation.points) {
            // sum += sqrt(point.x * point.x)  - sqrt(point.y * point.y);  // cppcheck-suppress unreadVariable
            auto pt = transformMatrix * glm::vec3(point.x, point.y, 1.0f);
            sum += pt.x;
            // sum += point.x;
            // benchmark::DoNotOptimize(point);
          }
        }
      }
      total += sum;
      // benchmark::DoNotOptimize(sum);
      // benchmark::ClobberMemory();
    }
    std::cout << "the traditional total is " << total << std::endl;
    // 确保统计的是遍历的点数，而不是 contours 数量
    //   state.SetItemsProcessed(contours.size() * state.iterations());
  }
}
