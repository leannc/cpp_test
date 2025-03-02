//
// Created by kang on 2024/12/13.
//
#include "UseCase.h"

void func1() noexcept {
  std::cout << "normal return" << std::endl;
  int i = 1;
  auto a = 30 / (i - 1);
}

void noexcept_usage() { func1(); }
