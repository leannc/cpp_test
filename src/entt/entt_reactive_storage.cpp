#include "Common.h"
#include <functional>

// NOTE ：这个reactive_storage，除了能够存储entity以外，还可以存储一个模板类型，用于辅助信息，非常有用

using reactive_storage = entt::reactive_mixin<entt::storage<bool>>;

void ConstructPosition(reactive_storage& storage, const entt::registry& reg, const entt::entity entity) {
  //   std::cout << "position constructed" << std::endl;
  storage.emplace(entity, false);
}

void DestroyPosition(reactive_storage& storage, const entt::registry& reg, const entt::entity entity) {
  //   std::cout << "position constructed" << std::endl;
  storage.remove(entity);
}

void entt_reactive_storage() {
  Document doc;
  reactive_storage storage;
  reactive_storage storage_only_larger_than_10;
  storage.bind(doc.registry_);
  storage_only_larger_than_10.bind(doc.registry_);

  storage.on_construct<Position, &ConstructPosition>();
  storage.on_destroy<Position, &DestroyPosition>();

  storage_only_larger_than_10
      .on_construct<Position, [](reactive_storage& storage, const entt::registry& reg, const entt::entity entity) {
        storage.remove(entity);
        auto pos = reg.get<Position>(entity);
        if (pos.x > 10) {
          storage.emplace(entity);
        }
      }>();

  storage_only_larger_than_10.on_destroy<Position, &DestroyPosition>();

  auto entity_1 = doc.registry_.create();
  doc.registry_.emplace<Position>(entity_1, 11, 1);

  auto entity_2 = doc.registry_.create();
  doc.registry_.emplace<Position>(entity_2, 2, 2);

  auto entity_3 = doc.registry_.create();

  for (auto [entity, flag] : storage.each()) {
    auto pos = doc.registry_.get<Position>(entity);
    std::cout << pos.x << ", " << pos.y << std::endl;
  }

  for (auto [entity, flag] : storage_only_larger_than_10.each()) {  // 只会有entity_1,因为entity_2不满足x的值的条件
    auto pos = doc.registry_.get<Position>(entity);
    std::cout << pos.x << ",, " << pos.y << std::endl;
  }
  std::cout << std::endl;
  doc.registry_.destroy(entity_2);

  for (auto [entity, flag] : storage.each()) {  // 删除以后，这个就只剩下entity_1了
    auto pos = doc.registry_.get<Position>(entity);
    std::cout << pos.x << ", " << pos.y << std::endl;
  }
  std::cout << std::endl;

  doc.registry_.remove<Position>(entity_1);

  for (auto [entity, flag] : storage.each()) {  // 一个都不剩了
    auto pos = doc.registry_.get<Position>(entity);
    std::cout << pos.x << ", " << pos.y << std::endl;
  }
  std::cout << std::endl;
}
