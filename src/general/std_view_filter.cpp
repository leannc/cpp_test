#include "UseCase.h"
#include <ranges>

void std_view_filter() {
  std::vector<int> numbers = {1, 2, 3, 4, 5};
  auto even_view = numbers | std::views::filter([](int x) { return x % 2 == 0; });

  // 第一次迭代
  for (int& num : even_view) {
    std::cout << num++ << " ";
  }
  std::cout << std::endl;

  auto even_view2 = numbers | std::views::filter([](int x) { return x % 2 == 0; });
  // 修改原始容器
  //   numbers = {6, 7, 8, 9, 10};

  // 重新创建视图
  //   even_view = numbers | std::views::filter([](int x) { return x % 2 == 0; });

  // 第二次迭代
  for (int num : even_view) {  // 这里会出错，因为之前已经把offset cache了
    std::cout << num << " ";
  }
  std::cout << std::endl;

  for (int num : numbers) {
    std::cout << num << " ";
  }
  std::cout << std::endl;
  for (int num : even_view2) {  // 这里就是正确的，因为是重新建了一个filter，有自己的cache
    std::cout << num << " ";
  }

  std::cout << std::endl;
}
