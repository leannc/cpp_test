//
// Created by kang on 2023/11/21.
//
#include "UseCase.h"

// #define REGISTER_TO_CHAIN(classname)

// #define REGISTER_TO_CHAIN_impl(target_class,class_following_the_target) \
//    static target_class target_class##_register_instance;              \
//    Animal::RegisterToAnimal(#target_class,&target_class##_register_instance)

#define REGISTER_TO_CHAIN(...) REGISTER_TO_CHAIN_impl(__VA_ARGS__, _front_)

#define PRINT_FUNCTION() std::cout << "Function: " << __func__ << std::endl;
class Animal {
 public:
  template <typename T> static void RegisterToAnimal() {
    static T instance;
    std::string name = instance.name();
    std::cout << "registering " << name << " to " << name << std::endl;

    if (std::find(class_names.begin(), class_names.end(), name) ==
        class_names.end()) {
      class_names.push_back(name);
      //            animals.push_back(animal);
    }
  }

  void shout() { std::cout << this->name() << " shouted" << std::endl; }

  virtual std::string name() = 0;

 public:
  static std::list<Animal *> animals;
  static std::list<std::string> class_names;
};

std::list<Animal *> Animal::animals;
std::list<std::string> Animal::class_names;

class Dog : public Animal {
 public:
  std::string name() override { return "dog"; }
};

class Cat : public Animal {
 public:
  std::string name() override { return "cat"; }
};

void polymorphism_dynamic_registry() {
  //    REGISTER_TO_CHAIN(Dog);
  //    REGISTER_TO_CHAIN(Cat,Dog);
  Animal::RegisterToAnimal<Dog>();

  for (auto &animal : Animal::animals) {
    animal->shout();
  }
}
