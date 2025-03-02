//
// Created by kang on 2024/12/22.
//

#include "UseCase.h"

#include <cstdio>
#include <iostream>
#include <memory>
#include <string>

namespace {
class MyClass {  // NOTE: 在匿名空间中的类,只有这cpp个文件看得见,就不会跟别的文件打搅
 public:
  explicit MyClass(std::string &&name) : name_(std::move(name)) {
    std::cout << name_ << " is constructed" << std::endl;
  }
  ~MyClass() { std::cout << name_ << " is destroyed" << std::endl; }
  std::string name() const { return name_; }

 private:
  std::string name_;
};

}  // namespace

void std_unique_ptr_custom_deleter_should_call_delete_raw_ptr_inside() {
  auto no_delete_deleter = [](MyClass *p) {
    if (p) {
      std::cout << "Deleting " << p->name() << " via no_delete_deleter deleter...\n";
      //    delete p;
    }
  };

  auto with_delete_deleter = [](MyClass *p) {
    if (p) {
      std::cout << "Deleting " << p->name() << " via with_delete_deleter deleter...\n";
      delete p;
    }
  };

  std::unique_ptr<MyClass> c1(new MyClass("c1"));
  std::unique_ptr<MyClass, decltype(no_delete_deleter)> c2(new MyClass("c2"),
                                                           no_delete_deleter);  // NOTE: c2的析构函数不会被调用
  std::unique_ptr<MyClass, decltype(with_delete_deleter)> c3(new MyClass("c3"), with_delete_deleter);

  return;
}
