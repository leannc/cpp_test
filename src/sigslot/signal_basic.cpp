#include <sigslot/signal.hpp>

void freeFunction() { std::cout << "free function" << std::endl; }

struct StructA {
  void memberFunction() { std::cout << "member function" << std::endl; }
  static void staticMemberFunction() { std::cout << "static member function" << std::endl; }
};

struct FunctionObject {
  void operator()() { std::cout << "function object" << std::endl; }
};

void signal_basic() {
  StructA object;
  auto lambda = []() { std::cout << "lambda\n"; };
  auto gen_lambda = [](auto&&... a) { std::cout << "generic lambda\n"; };

  // declare a signal instance with no arguments
  sigslot::signal<> sig;

  // connect slots
  sig.connect(freeFunction);
  sig.connect(&StructA::memberFunction, &object);
  sig.connect(&StructA::staticMemberFunction);
  sig.connect(FunctionObject());
  sig.connect(lambda);
  sig.connect(gen_lambda);

  // a free connect() function is also available
  sigslot::connect(sig, freeFunction);

  // emit a signal
  sig();
}
