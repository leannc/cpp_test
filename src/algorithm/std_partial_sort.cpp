#include "UseCase.h"

static void print(const auto& s, int middle) {
  for (int a : s) {
    std::cout << a << ' ';
  }
  std::cout << '\n';
  if (middle > 0) {
    while (middle-- > 0) {
      std::cout << "--";
    }
    std::cout << '^';
  } else if (middle < 0) {
    for (auto i = s.size() + middle; --i; std::cout << "  ") {}

    for (std::cout << '^'; middle++ < 0; std::cout << "--") {}
  }
  std::cout << '\n';
}

void std_partial_sort() {
  std::array<int, 10> s{5, 7, 4, 2, 8, 6, 1, 9, 0, 3};
  print(s, 0);
  //   std::partial_sort(s.begin(), s.begin() + 3, s.end());
  std::partial_sort(s.begin() + 3, s.begin() + 8, s.begin() + 8, std::greater{});
  print(s, 8);
  //   std::partial_sort(s.rbegin(), s.rbegin() + 4, s.rend());
  //   print(s, -4);
  //   std::partial_sort(s.rbegin(), s.rbegin() + 5, s.rend(), std::greater{});
  //   print(s, -5);
}
