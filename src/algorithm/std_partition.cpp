//
// Created by kang on 2024/12/13.
//

#include "UseCase.h"
#include <array>

void std_partition() {
  std::vector<int> v(10);
  std::iota(std::begin(v), std::end(v), 1);

  std::vector<int> even, odd;

  std::partition_copy(std::begin(v), std::end(v), std::back_inserter(even), std::back_inserter(odd),
                      [](int i) { return i % 2 == 0; });

  std::cout << "even number:" << std::endl;
  for (auto n : even) {
    std::cout << n << std::endl;
  }

  std::cout << "odd number:" << std::endl;
  for (auto n : odd) {
    std::cout << n << std::endl;
  }

  std::array<char, 8> src{'a', '2', '5', '7', 'b', 'c', '0', '\n'};

  auto tail = std::ranges::partition(src, [](char c) { return std::isdigit(c); });

  std::cout << "digit in src:" << std::endl;
  std::for_each(std::begin(src), std::begin(tail), [](char c) { std::cout << c << std::endl; });
  std::cout << "end" << std::endl;

  std::cout << "chars in src:" << std::endl;
  std::ranges::for_each(tail, [](char c) { std::cout << c << std::endl; });
  std::cout << "end" << std::endl;

  std::cout << "entire in src:" << std::endl;
  std::ranges::for_each(src, [](char c) { std::cout << c << std::endl; });
  std::cout << "end" << std::endl;

  //    for(auto c:src) std::cout<<c<<std::endl;
}
