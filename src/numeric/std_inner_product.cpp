#include <numeric>

void std_inner_product() {
  std::vector<int> v1(3, 1);
  std::vector<int> v2(4, 9);

  assert(v1.size() <= v2.size() && "the size of v2 should be greater than v1");

  int result_default = std::inner_product(std::begin(v1), std::end(v1), std::begin(v2), 0);
  int result_with_initial_value = std::inner_product(std::begin(v1), std::end(v1), std::begin(v2), 2);

  int costum_result =
      std::inner_product(std::begin(v1), std::end(v1), std::begin(v2), 0, std::plus<int>(), std::multiplies<int>());
  int costum_result_2 =
      std::inner_product(std::begin(v1), std::end(v1), std::begin(v2), 1, std::multiplies<int>(), std::plus<int>());

  std::cout << "result_default: " << result_default << std::endl;
  std::cout << "result_with_initial_value: " << result_with_initial_value << std::endl;
  std::cout << "costum_result: " << costum_result << std::endl;
  std::cout << "costum_result_2: " << costum_result_2 << std::endl;

  return;
}
