#include "Common.h"

void entt_basic_view() {
  Document doc;
  auto entity_1 = doc.registry_.create();

  Position& pos_1 = doc.registry_.emplace<Position>(entity_1);
  pos_1.x = 1.0f;
  pos_1.y = 1.0f;

  Velocity& vel_1 = doc.registry_.emplace<Velocity>(entity_1);
  vel_1.dx = 2.0f;
  vel_1.dy = 2.0f;

  auto entity_2 = doc.registry_.create();
  Position& pos_2 = doc.registry_.emplace<Position>(entity_2, 2.0f, 3.0f);
  Position& pos_3 = doc.registry_.patch<Position>(entity_2, [](auto& pos) { pos.x = 10.0f; });

  auto entity_3 = doc.registry_.create();
  Velocity& vel_3 = doc.registry_.emplace<Velocity>(entity_3);
  doc.registry_.remove<Position>(entity_3);

  doc.registry_.sort<Position>([](const Position& lhs, const Position& rhs) { return lhs.x < rhs.x; });

  auto view = doc.registry_.view<Position>();

  for (auto entity : view) {
    auto& pos = view.get<Position>(entity);
    std::cout << pos.x << ", " << pos.y << std::endl;
  }
}
