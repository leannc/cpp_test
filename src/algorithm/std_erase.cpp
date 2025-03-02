//
// Created by kang on 2024/11/3.
//
#include "UseCase.h"

void std_erase() {
  std::vector<int> v{3, 5, 7, 1, 4, 3, 8, 4, 2, 46, 2, 1};

  std::for_each(v.begin(), v.end(),
                [](int element) { std::cout << element << ","; });
  std::cout << std::endl;

  int value = 3;
  std::erase(v, value);
  std::cout << "------------ after std::erase " << value
            << ",the vector is -----------" << std::endl;
  std::for_each(v.begin(), v.end(),
                [](int element) { std::cout << element << ","; });
  std::cout << std::endl;

  std::erase_if(v, [](int i) { return i % 2 == 0; });
  std::cout << "------------ after std::erase_if ,the vector is -----------"
            << std::endl;
  std::erase(v, value);
  std::for_each(v.begin(), v.end(),
                [](int element) { std::cout << element << ","; });
  std::cout << std::endl;

  //    auto tail=std::partition(std::begin(v),std::end(v),[](int i){return
  //    i%2!=0;}); std::erase()

  std::vector<int> v2{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  v2.erase(v2.begin(), v2.begin() + 2);
  std::cout << "-----v2--------" << std::endl;
  for (auto &e : v2) {
    std::cout << e << std::endl;
  }
}
