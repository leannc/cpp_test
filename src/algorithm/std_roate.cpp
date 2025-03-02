//
// Created by kang on 2024/12/13.
//

#include "UseCase.h"

/**
 * std::rotate会直接改变原来的容器。
 * std::rotate_copy是不会改变原来的容器的，只会把结果搞出来，搞成新的容器。
 * */

void std_roate() {
  std::vector<int> v(10);
  std::iota(std::begin(v), std::end(v), 1);

  auto print_vec = [](int i) { std::cout << i << std::endl; };

  std::cout << "origin order " << std::endl;
  std::for_each(std::begin(v), std::end(v), print_vec);

  // 2 3 4 5 变成 4 5 2 3
  std::vector<int> v2;
  std::rotate_copy(std::ranges::find(v, 2), std::ranges::find(v, 4), std::ranges::find(v, 5) + 1,
                   std::back_inserter(v2));
  std::cout << "change 2 3 4 5  to  4 5 2 3" << std::endl;
  std::for_each(std::begin(v2), std::end(v2), print_vec);

  // 将5和2调换
  std::vector<int> v3;
  auto begin_itr = std::ranges::find(v, 2);
  auto mid_itr = std::ranges::find(v, 5);
  auto end_itr = mid_itr + 1;  /// end是指向的最后一个元素的下一位，这里找到的mid_itr是5，需要把5包括进来，所以要+1

  std::rotate_copy(begin_itr, mid_itr, end_itr, std::back_inserter(v3));
  std::rotate(std::ranges::find(v3, 2), std::ranges::find(v3, 3), std::end(v3));

  std::cout << "switch 5 and 2 " << std::endl;
  std::for_each(std::begin(v3), std::end(v3), print_vec);
}
