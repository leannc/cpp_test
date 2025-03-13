#include "Common.h"

// NOTE 可以动态识别基本的成员，还可以识别vector内的元素。
// NOTE 像下面的CompliateData，在其数据结构里面有vector指针，就需要重写拷贝构造函数，才能支持这种序列化的效果。

void entt_copy_entity() {
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

  auto dest_1 = registry.create();

  // create a copy of an entity component by component
  for (auto&& curr : registry.storage()) {
    if (auto& storage = curr.second; storage.contains(src_1)) {
      storage.push(dest_1, storage.value(src_1));
    }
  }

  // 验证数据是否正确复制
  std::cout << std::endl;
  auto& pos = registry.get<Position>(dest_1);
  std::cout << "Position: (" << pos.x << ", " << pos.y << ")" << std::endl;

  std::cout << std::endl;
  auto& vel = registry.get<Velocity>(dest_1);
  std::cout << "Velocity: (" << vel.dx << ", " << vel.dy << ")" << std::endl;

  std::cout << std::endl;
  auto& less_complicate_data_2 = registry.get<LessComplicateData>(dest_1);
  for (auto& pos : less_complicate_data_2.positions_) {
    std::cout << "Position: (" << pos.x << ", " << pos.y << ")" << std::endl;
  }

  std::cout << std::endl;
  auto& complicate_data_2 = registry.get<ComplicateData>(dest_1);
  for (auto& pos : complicate_data_2.positions_) {
    std::cout << "Position: (" << pos->x << ", " << pos->y << ")" << std::endl;
  }
}
