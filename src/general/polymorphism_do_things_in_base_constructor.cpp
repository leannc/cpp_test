//
// Created by kang on 2023/11/21.
//
#include "UseCase.h"

class base {
 public:
  base() { animals.push_back(this); }

  void shout() { std::cout << this->name() << " shouted" << std::endl; }

  virtual std::string name() = 0;

 public:
  static std::vector<base *> animals;
};

std::vector<base *> base::animals;

class dog : public base {
  std::string name() override { return "dog"; }
};

class cat : public base {
  std::string name() override { return "cat"; }
};

void polymorphism_do_things_in_base_constructor() {
  dog d;
  cat c;

  for (auto &animal : base::animals) {
    animal->shout();
  }
}
