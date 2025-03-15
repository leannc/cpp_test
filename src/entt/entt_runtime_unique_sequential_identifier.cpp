#include "Common.h"
// 定义基础的游戏组件类型
using GameFamily = entt::family<struct GameTags>;

struct HealthComponent {
  int value;
};

// 定义自定义的运行时生成器标签

// 模拟插件引入的新组件类型
struct MagicComponent {
  int mana;
};

struct ShieldComponent {
  bool enabled;
};

// 模拟游戏系统中根据组件标识符处理组件的函数
void handleComponent(int componentIdentifier, entt::entity entity, const entt::registry& registry) {
  if (componentIdentifier == GameFamily::value<HealthComponent>) {
    auto& health = registry.get<HealthComponent>(entity);
    std::cout << "Handling HealthComponent for entity: " << static_cast<unsigned int>(entity)
              << ", Health value: " << health.value << std::endl;
  } else if (componentIdentifier == GameFamily::value<MagicComponent>) {
    auto& magic = registry.get<MagicComponent>(entity);
    std::cout << "Handling MagicComponent for entity: " << static_cast<unsigned int>(entity)
              << ", Mana value: " << magic.mana << std::endl;
  } else if (componentIdentifier == GameFamily::value<ShieldComponent>) {
    auto& shield = registry.get<ShieldComponent>(entity);
    std::cout << "Handling ShieldComponent for entity: " << static_cast<unsigned int>(entity)
              << ", Shield enabled: " << (shield.enabled ? "true" : "false") << std::endl;
  } else {
    std::cout << "Unknown component type for entity: " << static_cast<unsigned int>(entity) << std::endl;
  }
}
void entt_runtime_unique_sequential_identifier() {
  entt::registry registry;

  // 创建一个实体并添加基础组件
  auto entity = registry.create();
  auto health_comp = registry.emplace<HealthComponent>(entity, 100);

  // 获取 HealthComponent 的运行时标识符并处理
  int healthIdentifier = GameFamily::value<HealthComponent>;
  handleComponent(healthIdentifier, entity, registry);

  // 模拟插件安装，添加新组件
  registry.emplace<MagicComponent>(entity, 50);
  registry.emplace<ShieldComponent>(entity, true);

  // 获取新组件的运行时标识符并处理
  int magicIdentifier = GameFamily::value<MagicComponent>;
  handleComponent(magicIdentifier, entity, registry);

  int shieldIdentifier = GameFamily::value<ShieldComponent>;
  handleComponent(shieldIdentifier, entity, registry);
}
