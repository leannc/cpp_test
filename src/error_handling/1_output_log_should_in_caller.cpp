#include "UseCase.h"

/**
 * NOTE:在调用函数时，需要输出的log应该由调用者负责，而不是被调用者
 */
int mysqrt(int x) {
  if (x < 0) {
    return -1;
  }

  for (int i = 0;; i++) {
    if (i * i >= x) {
      return i;
    }
  }
}

void output_log_should_in_caller() {
  int ret = mysqrt(-4);
  if (ret == -1) {
    std::cout << "sqrt's param should greater than zero. and this log should be printed here,not in sqrt function"
              << std::endl;
  } else {
    std::cout << "sqrt result is" << ret << std::endl;
  }
}
