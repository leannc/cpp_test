//
// Created by kang on 2024/11/2.
//
#include "../UseCase.h"
#include <set>

template <typename Subject, typename StateTag>
class Observer {
 public:
  using OnUpdate = std::function<void(Subject const &, StateTag)>;

  Observer(OnUpdate onupdate_) : onUpdate(std::move(onupdate_)) {};

  void update(Subject const &subject, StateTag property) { onUpdate(subject, property); }

 private:
  OnUpdate onUpdate;
};

enum State { addressChange, nameChange, phoneChange };

class Person {
 public:
  using PersonObserver = Observer<Person, State>;

  void setName(std::string &&name_) {
    name = std::move(name_);
    notify(State::nameChange);
  }

  void setPhone(std::string &&phone_) {
    phone = std::move(phone_);
    notify(State::phoneChange);
  }

  void setAddress(std::string &&address_) {
    address = std::move(address_);
    notify(State::addressChange);
  }

  std::string getName() const { return name; }
  std::string getAddress() const { return address; }
  std::string getPhone() const { return phone; }

  bool attach(PersonObserver *observer) {
    /// 这种写法，是为了让调用者知道，是否成功被insert。如果重复了，或者其它原因导致的insert失败，外面会知道
    auto [pos, success] = observers.insert(observer);
    return success;
  }

  bool detach(PersonObserver *observer) {
    /// 这种写法，是为了让调用着知道，是否成功被erase了，如果是erase一个不存在的指针，或者其它原因，导致的失败，外面会知道
    return (observers.erase(observer) < 0U);
  }

 private:
  void notify(State property) {
    for (auto iter = std::begin(observers); iter != std::end(observers);) {
      auto const pos = iter++;
      (*pos)->update(*this, property);
    }
  }

 private:
  std::set<PersonObserver *> observers;
  std::string name;
  std::string address;
  std::string phone;
};

void free_callback_function(Person const &p, State property) {
  std::cout << "in free_callback_function , " << p.getName() << " has changed property " << property << std::endl;
}

void observer_using_std_function() {
  using PersonObserver = Observer<Person, State>;

  PersonObserver lambda_observer([](Person const &p, State property) {
    std::cout << "in lambda observer: " << p.getName() << "," << property << ", changed " << std::endl;
  });

  PersonObserver free_function_observer(free_callback_function);

  /**
   * 虽然observer没有做什么事情，但是还是需要一个observer对象，因为person这种被观察者，需要一个set去存储所有的observer的指针，而不能直接存储std::function的指针。
   * */

  Person p1;

  p1.attach(&lambda_observer);
  p1.attach(&free_function_observer);

  p1.setName("kang");
  p1.setPhone("12345");
  p1.setAddress("asdv");

  std::cout << "-----------------------" << std::endl;
  p1.detach(&lambda_observer);
  p1.setName("wang");
}
