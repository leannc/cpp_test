#include "Common.h"
#include <fstream>

#include <cereal/archives/binary.hpp>
#include <cereal/types/vector.hpp>

void entt_snapshot_with_cereal() {
  entt::registry registry;

  // 创建一些实体并添加Position组件
  auto e1 = registry.create();
  registry.emplace<Position>(e1, 1.0f, 2.0f);
  registry.emplace<Velocity>(e1, 1.10f, 2.1f);
  auto e2 = registry.create();
  registry.emplace<Position>(e2, 3.0f, 4.0f);
  registry.emplace<Velocity>(e2, 3.3f, 4.3f);

  // 将数据序列化到文件
  {
    std::ofstream ofs("data11.bin", std::ios::binary);
    cereal::BinaryOutputArchive oarchive(ofs);

    // 使用Entt的snapshot进行序列化
    entt::snapshot{registry}.get<entt::entity>(oarchive).get<Velocity>(oarchive).get<Position>(oarchive);
  }

  // 清空注册表
  registry.clear();

  entt::registry registry2;
  // 从文件中反序列化数据并恢复到注册表
  {
    std::ifstream ifs("data11.bin", std::ios::binary);
    cereal::BinaryInputArchive iarchive(ifs);

    // 使用Entt的snapshot_loader进行反序列化
    entt::snapshot_loader{registry2}
        .get<entt::entity>(iarchive)
        .get<Velocity>(iarchive)
        .get<Position>(iarchive)
        .orphans();
  }

  entt::registry registry3;
  auto e3 = registry3.create();
  registry3.emplace<Position>(e1, 21.0f, 32.0f);
  registry3.emplace<Velocity>(e1, 21.10f, 32.1f);
  {
    std::ifstream ifs("data11.bin", std::ios::binary);
    cereal::BinaryInputArchive iarchive(ifs);

    // 使用Entt的continuous_loader进行反序列化
    entt::continuous_loader{registry3}
        .get<entt::entity>(iarchive)
        .get<Velocity>(iarchive)
        .get<Position>(iarchive)
        .orphans();
  }

  // 验证数据是否正确恢复
  auto view = registry2.view<Position, Velocity>();
  for (auto entity : view) {
    const auto& [pos, vel] = view.get<Position, Velocity>(entity);
    std::cout << "Entity: " << ", Position: (" << pos.x << ", " << pos.y << ")" << std::endl;
    std::cout << "Velocity: (" << vel.dx << ", " << vel.dy << ")" << std::endl;
    std::cout << std::endl;
  }
  std::cout << "continous loading---------" << std::endl;
  view = registry3.view<Position, Velocity>();
  for (auto entity : view) {
    const auto& [pos, vel] = view.get<Position, Velocity>(entity);
    std::cout << "Entity: " << ", Position: (" << pos.x << ", " << pos.y << ")" << std::endl;
    std::cout << "Velocity: (" << vel.dx << ", " << vel.dy << ")" << std::endl;
    std::cout << std::endl;
  }
}
