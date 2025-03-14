#include "Common.h"

// NOTE : 这个view的具体类型，可以根据实际情况动态指定，方便runtime的灵活处理

void entt_runtime_view() {
  entt::registry registry;

  // 创建一些实体并添加组件
  auto entity1 = registry.create();
  registry.emplace<Position>(entity1, 0.0f, 0.0f);
  registry.emplace<Velocity>(entity1, 1.0f, 1.0f);

  auto entity2 = registry.create();
  registry.emplace<LessComplicateData>(entity2);

  auto entity3 = registry.create();
  registry.emplace<ComplicateData>(entity3);

  entt::runtime_view view;
  std::string skillName = "movement_skill";

  if (skillName == "movement_skill") {
    // 该技能影响具有 Position 和 Velocity 组件的实体
    view.iterate(registry.storage<Position>()).iterate(registry.storage<Velocity>());
  } else if (skillName == "healing_skill") {
    // 该技能影响具有 Health 组件的实体
    view.iterate(registry.storage<LessComplicateData>());
  } else if (skillName == "mana_drain_skill") {
    // 该技能影响具有 Mana 组件的实体
    view.iterate(registry.storage<ComplicateData>());
  }

  view.each([&registry](auto entity) {
    if (registry.all_of<Position, Velocity>(entity)) {
      auto& pos = registry.get<Position>(entity);
      auto& vel = registry.get<Velocity>(entity);

      std::cout << "pos : " << pos.x << ", " << pos.y << std::endl;
      std::cout << "vel : " << vel.dx << ", " << vel.dy << std::endl;

    } else if (registry.all_of<LessComplicateData>(entity)) {
      std::cout << "less complicate data" << std::endl;
    } else if (registry.all_of<ComplicateData>(entity)) {
      std::cout << "complicate data" << std::endl;
    }
  });
}
