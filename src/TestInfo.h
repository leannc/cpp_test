//
// Created by kang on 2023/11/21.
//

#pragma once

#include <iostream>
#include <string>

#define CALL_USE_CASE(func)                                                                                            \
  std::cout << "--------------------------------------------" << std::endl;                                            \
  std::cout << #func << std::endl;                                                                                     \
  std::cout << "--------------------------------------------" << std::endl;                                            \
  func();                                                                                                              \
//    footer(#func);
