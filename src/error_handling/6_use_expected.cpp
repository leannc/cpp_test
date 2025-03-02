#include "UseCase.h"
#include "error_code/login_error_code.h"
#include <tl/expected.hpp>

tl::expected<int, std::error_code> login_custom_errocode_expected(int x) {
  if (x < 0) {
    return tl::unexpected{make_error_code(login_error::invalid_input)};
  }

  if (x == 4) {
    return tl::unexpected{make_error_code(std::errc::address_in_use)};
  }

  for (int i = 0;; i++) {
    if (i * i >= x) {
      return i;
    }
  }
}

tl::expected<int, std::error_code> nest_call(int x) {
  if (x < 1) {
    return tl::unexpected{make_error_code(std::errc::invalid_seek)};
  }

  auto ret = login_custom_errocode_expected(x);
  return ret.map_error([](std::error_code &err) {
    std::cout << "in map error function " << std::endl;
    return err;
  });
}

void use_expected() {
  auto ret = login_custom_errocode_expected(-4);
  if (false == ret.has_value()) {
    std::cout << ret.error().message()
              << std::endl;  //---- 这里ec.message() 其实就是调用了 ec.category().message(ec.value());是一个简化的写法
  } else {
    std::cout << "sqrt result is " << ret.value() << std::endl;
  }

  ret = login_custom_errocode_expected(4);
  if (false == ret.has_value()) {
    std::cout << ret.error().message() << std::endl;
  } else {
    std::cout << "sqrt result is " << ret.value() << std::endl;
  }

  ret = login_custom_errocode_expected(8);
  if (false == ret.has_value()) {
    std::cout << ret.error().message() << std::endl;
  } else {
    std::cout << "sqrt result is " << ret.value() << std::endl;
  }
}
