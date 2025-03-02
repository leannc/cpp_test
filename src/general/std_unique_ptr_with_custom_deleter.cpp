//
// Created by kang on 2024/12/22.
//

#include "UseCase.h"

#include <cstdio>
#include <iostream>
#include <memory>
#include <string>

// 自定义一个 deleter，让 unique_ptr 析构时自动调用 fclose

void std_unique_ptr_with_custom_deleter() {
  // 打开文件
  auto FileCloser = [](FILE *fp) {
    if (fp) {
      std::cout << "Closing file via custom deleter...\n";
      std::fclose(fp);
      // delete fp;  // NOTE:fclose后面是不需要再加delete的,cppreference上也没加
    }
  };

  // 使用自定义的 deleter，让 unique_ptr 在析构时调用 fclose
  std::cout << "Open" << std::endl;
  FILE *file = std::fopen("README.MD", "r");
  std::unique_ptr<FILE, decltype(FileCloser)> filePtr{file, FileCloser};

  // 这里可以进行文件读取或其他操作
  // ...
  char buffer[128];
  if (std::fgets(buffer, sizeof(buffer), filePtr.get()) != nullptr) {
    std::cout << "Read line: " << buffer << '\n';
  }

  // 当 filePtr 离开作用域时，FileCloser 会被调用，从而自动 fclose(fp)
  return;
}
