#include "Common.h"
#include <fstream>

#include <memory>
#include <vector>

#include <cereal/archives/binary.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/vector.hpp>

void entt_serialize_pointer() {
  entt ::registry registry;

  // 创建一些 Position 对象并添加到 registry 和 ComplicateData
  auto pos1 = std::make_shared<Position>(1.0f, 2.0f);
  auto pos2 = std::make_shared<Position>(3.0f, 4.0f);

  auto entity_1 = registry.create();
  auto& data_1 = registry.emplace<ComplicateData>(entity_1);
  data_1.positions_.push_back(pos1);
  data_1.positions_.push_back(pos2);

  data_1.my_position_ = std::make_unique<Position>(5.0f, 6.0f);

  // 保存数据到文件
  {
    std ::ofstream ofs("data.bin", std::ios::binary);
    cereal ::BinaryOutputArchive archive(ofs);

    // 保存注册表
    entt ::snapshot saver{registry};
    saver.get<entt::entity>(archive);
    saver.get<ComplicateData>(archive);
  }

  // 清空 registry 和 data
  registry.clear();
  entt ::registry registry2;
  // 从文件加载数据
  {
    std ::ifstream ifs("data.bin", std::ios::binary);
    cereal ::BinaryInputArchive archive(ifs);

    // 加载注册表
    entt ::snapshot_loader loader{registry2};
    loader.get<entt::entity>(archive);
    loader.get<ComplicateData>(archive);
    loader.orphans();
  }

  // 验证加载的数据
  auto view = registry2.view<ComplicateData>();
  for (const auto& entity : view) {
    auto& data = view.get<ComplicateData>(entity);
    for (auto& pos : data.positions_) {
      std::cout << "Position: ( " << pos->x << ", " << pos->y << " )" << std::endl;
    }
    std::cout << "My Position: ( " << data.my_position_->x << ", " << data.my_position_->y << " )" << std::endl;
  }
}
