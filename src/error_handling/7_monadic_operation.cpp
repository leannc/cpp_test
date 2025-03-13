#include "UseCase.h"
#include "error_code/login_error_code.h"
#include <tl/expected.hpp>

#define EXPECT(x) tl::expected<x, std::error_code>

EXPECT(int) add(int a, int b) {
  if (a < 10) {
    return a + b;
  } else {
    return tl::unexpected{make_error_code(login_error::invalid_input)};
  }
}

EXPECT(int) square(int num) {
  if (num < 0) {
    return tl::unexpected{make_error_code(login_error::out_of_range)};
  } else {
    return num * num;
  }
}

EXPECT(int) error_handling(const std::error_code& code) {
  std::cout << "error:" << code.message() << std::endl;
  return tl::unexpected{code};
}

void monadic_operation() {
  auto result = add(2, 0).and_then(square).or_else(&error_handling);

  if (result.has_value()) {
    std::cout << "result is : " << result.value() << std::endl;
  } else {
    std::cout << "no valid result" << std::endl;
  }
}
