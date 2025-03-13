#include "Common.h"

// 简单的输出存档
class OutputArchive {
 public:
  template <typename T>
  void operator()(const T& value) {
    // 使用 insert 方法插入一段内存区域的数据
    data.insert(data.end(), reinterpret_cast<const char*>(&value), reinterpret_cast<const char*>(&value) + sizeof(T));
  }
  std ::vector<char> data;
};

// 简单的输入存档
class InputArchive {
 public:
  InputArchive(const std::vector<char>& data) : data(data), pos(0) {}

  template <typename T>
  void operator()(T& value) {
    std::memcpy(&value, data.data() + pos, sizeof(T));
    pos += sizeof(T);
  }

 private:
  const std::vector<char>& data;
  size_t pos;
};

void entt_snapshot() {
  entt::registry registry;

  // 创建实体并添加组件
  auto entity = registry.create();
  registry.emplace<Position>(entity, 10.0f, 20.0f);
  registry.emplace<Velocity>(entity, 1.0f, 1.0f);

  // 创建快照
  OutputArchive output;
  entt::snapshot{registry}.get<entt::entity>(output).get<Position>(output).get<Velocity>(output);

  // 使用快照加载器恢复到新的注册表
  entt::registry newRegistry;
  InputArchive input(output.data);
  entt::snapshot_loader{newRegistry}.get<entt::entity>(input).get<Position>(input).get<Velocity>(input).orphans();

  // 验证恢复结果
  newRegistry.view<Position, Velocity>().each([](const auto& pos, const auto& vel) {
    std::cout << "Position: (" << pos.x << ", " << pos.y << ")" << std::endl;
    std::cout << "Velocity: (" << vel.dx << ", " << vel.dy << ")" << std::endl;
  });

  // 使用连续加载器恢复到可能非空的注册表
  entt::registry continuousRegistry;
  auto anotherEntity = continuousRegistry.create();
  continuousRegistry.emplace<Position>(anotherEntity, 5.0f, 5.0f);
  continuousRegistry.emplace<Velocity>(anotherEntity, 15.0f, 15.0f);

  InputArchive continuousInput(output.data);
  entt::continuous_loader loader{continuousRegistry};
  loader.get<entt::entity>(continuousInput).get<Position>(continuousInput).get<Velocity>(continuousInput).orphans();

  // 验证连续加载结果
  continuousRegistry.view<Position, Velocity>().each([](const auto& pos, const auto& vel) {
    std::cout << "Continuous Position: (" << pos.x << ", " << pos.y << ")" << std::endl;
    std::cout << "Continuous Velocity: (" << vel.dx << ", " << vel.dy << ")" << std::endl;
  });
}
