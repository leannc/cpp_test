//
// Created by kang on 2024/12/28.
//

#include "UseCase.h"

/**
 * std::find只能找到第一个出现的那一个元素，并返回它的 iterator，就完了。
 */
void std_find() {
  std::vector<char> src{'a', '2', '5', '7', 'b', 'c', '0', '\n'};

  auto it = std::find_if(src.begin(), src.end(),
                         [](char c) { return std::isdigit(c); });

  while (it != src.end()) {
    std::cout << *it << std::endl;
    it++;
  }
}
