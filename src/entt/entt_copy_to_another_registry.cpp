#include "Common.h"

// NOTE
// 如果是复制到另一个registry，如果另一个registry中没有相应的组件，也就是没有相应的storage，那这个组件就不会被复制。

void entt_copy_to_another_registry() {
  entt::registry registry;

  // 创建一些实体并添加Position组件
  auto src_1 = registry.create();
  registry.emplace<Position>(src_1, 1.0f, 2.0f);
  registry.emplace<Velocity>(src_1, 1.10f, 2.1f);
  auto& complicate_data = registry.emplace<ComplicateData>(src_1);
  auto& less_complicate_data = registry.emplace<LessComplicateData>(src_1);

  //   创建一些 Position 对象并添加到 registry 和 ComplicateData
  auto pos1 = std::make_shared<Position>(1.3f, 2.3f);
  auto pos2 = std::make_shared<Position>(3.3f, 4.3f);
  complicate_data.positions_.push_back(pos1);
  complicate_data.positions_.push_back(pos2);

  less_complicate_data.positions_.emplace_back(1.1f, 2.1f);
  less_complicate_data.positions_.emplace_back(3.1f, 4.1f);

  entt::registry registry2;

  auto dest_1 = registry2.create();
  auto dest_2 = registry2.create();
  registry2.emplace<Position>(dest_2, 11.0f, 12.0f);

  // NOTE 这里被注释了，导致registry2没有Velocity组件的storage，后面的dst_storage就会是nullptr
  // registry2.emplace<Velocity>(dest_2, 11.10f, 12.1f);

  // auto& tmp_complicate_data = registry2.emplace<ComplicateData>(dest_2);
  registry2.storage<ComplicateData>();  // 这样也可以初始化storage
  auto& tmp_less_complicate_data = registry2.emplace<LessComplicateData>(dest_2);

  // create a copy of an entity component by component
  for (auto&& [id, storage] : registry.storage()) {
    if (storage.contains(src_1)) {
      const auto dst_storage = registry2.storage(id);
      if (dst_storage) {
        dst_storage->push(dest_1, storage.value(src_1));
      }
    }
  }

  // 验证数据是否正确复制
  std::cout << std::endl;
  auto& pos = registry2.get<Position>(dest_1);
  std::cout << "Position: (" << pos.x << ", " << pos.y << ")" << std::endl;

  std::cout << std::endl;
  auto vel = registry2.try_get<Velocity>(dest_1);
  if (vel != nullptr) {
    std::cout << "Velocity: (" << vel->dx << ", " << vel->dy << ")" << std::endl;
  }

  std::cout << std::endl;
  auto& less_complicate_data_2 = registry2.get<LessComplicateData>(dest_1);
  for (auto& pos : less_complicate_data_2.positions_) {
    std::cout << "LessComplicateData Position: (" << pos.x << ", " << pos.y << ")" << std::endl;
  }

  std::cout << std::endl;
  auto& complicate_data_2 = registry2.get<ComplicateData>(dest_1);
  for (auto& pos : complicate_data_2.positions_) {
    std::cout << "ComplicateData Position: (" << pos->x << ", " << pos->y << ")" << std::endl;
  }
}
