#include "Common.h"
using namespace entt::literals;

void entt_multy_same_component_type() {
  entt::registry registry;
  // ----暂时不成功----
  // 创建一些实体并添加Position组件
  auto src_1 = registry.create();

  auto&& position_storage = registry.storage<Position>("second position"_hs);
  registry.emplace<Position>(src_1, 1.0f, 2.0f);
  position_storage.push(src_1);
  auto pos = reinterpret_cast<Position*>(position_storage.value(src_1));
  pos->x = 1.1;
  pos->y = 1.2;

  // direct initialization
  entt::basic_view direct{registry.storage<Position>(), registry.storage<Position>("second position"_hs)};

  // concatenation
  auto join = registry.view<Position>() | entt::basic_view{registry.storage<Position>("second position"_hs)};

  direct.each([](const auto entity, const auto& pos, const auto& pos2) {
    std::cout << "Entity: " << ", Position: (" << pos.x << ", " << pos.y << ")" << std::endl;
    std::cout << "Entity: " << ", Position2: (" << pos2.x << ", " << pos2.y << ")" << std::endl;
  });

  std::cout << std::endl;
  join.each([](const auto entity, const auto& pos, const auto& pos2) {
    std::cout << "Entity: " << ", Position: (" << pos.x << ", " << pos.y << ")" << std::endl;
    std::cout << "Entity: " << ", Position2: (" << pos2.x << ", " << pos2.y << ")" << std::endl;
  });
}
