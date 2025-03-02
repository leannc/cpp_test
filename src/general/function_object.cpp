#include "UseCase.h"

class Counter {
 public:
  Counter() : count(0) {}
  // 重载 () 运算符，每次调用计数器加 1
  void operator()() {
    ++count;
    std::cout << "Count: " << count << std::endl;
  }

 private:
  int count;
};

class FunctorObjectWithParam {
 public:
  FunctorObjectWithParam() : count(0) {}
  // 重载 () 运算符，每次调用计数器加 1
  void operator()(int add_param) {
    ++count;
    std::cout << "count is : " << count << ", add_param is : " << add_param << std::endl;
  }

 private:
  int count;
};

class SortFunctor {
 public:
  SortFunctor() {}
  // 重载 () 运算符，每次调用计数器加 1
  bool operator()(const int &a, const int &b) { return a > b; }
};

void function_object() {
  Counter counter;
  counter();
  counter();
  counter();

  FunctorObjectWithParam obj;
  obj(20);
  obj(3);
  obj(4);

  std::vector<int> v{80, 60, 70, 84, 45, 96, 37, 18, 69};
  std::sort(v.begin(), v.end(), SortFunctor{});
  for (const auto &i : v) {
    std::cout << i << " ";
  }
}
