#include "Common.h"
#include <stack>

using namespace entt::literals;

using TagA = entt::tag<"TagA"_hs>;
using TagB = entt::tag<"TagB"_hs>;
using TagC = entt::tag<"TagC"_hs>;

// 辅助函数，用于打印实体的标签
template <typename... Tags>
void printEntityTags(const entt::registry& registry, entt::entity entity) {
  (void)std::initializer_list<int>{
      ((registry.all_of<Tags>(entity))
           ? (std::cout << "Entity has tag: " << entt::type_id<Tags>().name() << std::endl, 0)
           : 0)...};
}

constexpr entt::id_type tag_a = "TagA"_hs;

void entt_tag() {
  entt::registry registry;
  auto entity = registry.create();
  registry.emplace<TagA>(entity);
  registry.emplace<TagB>(entity);
  registry.emplace<TagC>(entity);

  auto entity2 = registry.create();
  registry.emplace<TagA>(entity2);

  auto entity3 = registry.create();
  registry.emplace<TagA>(entity3);
  registry.emplace<TagB>(entity3);

  // printEntityTags<TagA, TagB, TagC>(registry, entity);

  std::stack<entt::id_type> s;
  s.push(tag_a);

  const entt::id_type val = s.top();
  std::cout << val << std::endl;

  // std::string str = "TagA";

  // const entt::id_type type_id_A = "TagA"_hs;
  // const entt::id_type type_id_A = entt::hashed_string::value("TagA");
  // const entt::id_type type_id_A = entt::hashed_string::value(str.c_str());

  auto view = registry.view<TagA>(entt::exclude<TagB>);  // 只有entity2，因为1,3都有TagB
  view.each([](auto entity) { std::cout << "Entity with TagA: " << static_cast<unsigned int>(entity) << std::endl; });
}
