#include "Common.h"

void entt_view_with_iterator() {
  entt::registry registry;

  // 创建一些实体并添加组件
  for (int i = 0; i < 5; ++i) {
    auto entity = registry.create();
    registry.emplace<Position>(entity, static_cast<float>(i), static_cast<float>(i * 2));
    registry.emplace<Velocity>(entity, static_cast<float>(i + 1), static_cast<float>(i + 2));

    if (i == 3) {
      registry.emplace<LessComplicateData>(entity);
    }
    if (i == 4) {
      registry.emplace<ComplicateData>(entity);
    }
  }

  // 创建视图
  auto view = registry.view<Position, Velocity>(entt::exclude<LessComplicateData>);

  // 使用 std::for_each 遍历视图
  std::for_each(view.begin(), view.end(), [&](auto entity) {
    auto& pos = view.get<Position>(entity);
    auto& vel = view.get<Velocity>(entity);

    // 更新位置
    pos.x += vel.dx;
    pos.y += vel.dy;

    std::cout << "Entity: " << static_cast<unsigned int>(entity) << ", New Position: (" << pos.x << ", " << pos.y << ")"
              << std::endl;
  });

  auto it = std::find_if(view.begin(), view.end(), [&](auto entity) {
    auto& pos = view.get<Position>(entity);
    return pos.x == 3.0f;
  });

  if (it != view.end()) {
    auto entity = *it;
    auto& pos = view.get<Position>(entity);
    std::cout << "Found entity: , Position: (" << pos.x << ", " << pos.y << ")" << std::endl;
  }
}
