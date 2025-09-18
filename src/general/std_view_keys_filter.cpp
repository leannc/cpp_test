#include "UseCase.h"
#include <ranges>

void std_view_keys_filter() {
  std::unordered_map<std::string, int> umap_;
  umap_["first"] = 1;
  umap_["second"] = 2;

  auto keys = std::views::keys(umap_);
  for (auto& key : keys) {
    std::cout << key << std::endl;
  }
}
