﻿#include <sigslot/signal.hpp>

struct foo {
  // Notice how we accept a double as first argument here.
  // This is fine because float is convertible to double.
  // 's' is a reference and can thus be modified.
  void bar(double d, int i, bool b, std::string& s) { s = b ? std::to_string(i) : std::to_string(d); }
  void more_param_bar(double d, int i, bool b, std::string& s, int e) {
    if (e == 0) {
      std::cout << "e == 0" << std::endl;
    } else {
      std::cout << "e == 1" << std::endl;
    }
  }
};

// Function objects can cope with default arguments and overloading.
// It does not work with static and member functions.
struct obj {
  void operator()(float, int, bool, std::string&, int = 0) { std::cout << "I was here\n"; }

  void operator()() {}
};

void signal_with_param() {
  // declare a signal with float, int, bool and string& arguments
  sigslot::signal<float, int, bool, std::string&> sig;

  // a generic lambda that prints its arguments to stdout
  auto printer = [](auto a, auto&&... args) {
    std::cout << a;
    (void)std::initializer_list<int>{((void)(std::cout << " " << args), 1)...};
    std::cout << "\n";
  };

  // connect the slots
  foo ff;
  auto func_0 = std::bind(&foo::more_param_bar, &ff, std::placeholders::_1, std::placeholders::_2,
                          std::placeholders::_3, std::placeholders::_4, 0);
  auto func_1 = std::bind(&foo::more_param_bar, &ff, std::placeholders::_1, std::placeholders::_2,
                          std::placeholders::_3, std::placeholders::_4, 1);

  sig.connect(func_0);
  sig.connect(func_1);

  sig.connect(printer);
  sig.connect(&foo::bar, &ff);
  sig.connect(obj());

  float f = 1.f;
  short i = 2;  // convertible to int
  std::string s = "0";

  // emit a signal
  sig(f, i, false, s);
  sig(f, i, true, s);
}
