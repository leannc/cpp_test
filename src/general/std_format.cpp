//
// Created by kang on 2024/12/30.
//

#include "UseCase.h"
#include <format>
#include <string>
#include <string_view>

template <typename... Args>
std::string dyna_print(std::string_view rt_fmt_str, Args &&...args) {
  return std::vformat(rt_fmt_str, std::make_format_args(args...));
}

void std_format() {
  std::string s = "my name is {0} {1}";

  auto res = std::vformat(s, std::make_format_args("wang", "kang"));

  std::cout << res << std::endl;

  std::string s2 = "my home is in {0} province, city of {1}";
  std::string res2 = dyna_print(s2, "hubei", "wuhan", "jianghan");
  std::cout << res2 << std::endl;
}
