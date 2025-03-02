//
// Created by kang on 2024/11/11.
//

#include "../../UseCase.h"

class Item {
 public:
  virtual ~Item() = default;
  virtual double price() = 0;
};

class Book : public Item {
 public:
  Book(double p, std::string t) : book_price(p), title(std::move(t)) {}
  double price() override { return book_price; }

 private:
  double book_price;
  std::string title;
};

class Conference : public Item {
 public:
  Conference(double p, std::string n) : conf_price(p), name(std::move(n)) {}
  double price() override { return conf_price; }

 private:
  double conf_price;
  std::string name;
};
//------------------------------------------
class DecoratedItem : public Item {
 public:
  explicit DecoratedItem(std::unique_ptr<Item> item) : item_(std::move(item)) {}

 protected:
  //    Item& item() {return *item_;}
  Item &item() const { return *item_; }

 private:
  std::unique_ptr<Item> item_;
};

class Discounted : public DecoratedItem {
 public:
  explicit Discounted(double discountRate, std::unique_ptr<Item> item)
      : discount_rate(discountRate), DecoratedItem(std::move(item)) {}
  double price() override { return item().price() * discount_rate; }

 private:
  double discount_rate;
};

class Taxed : public DecoratedItem {
 public:
  explicit Taxed(double taxRate, std::unique_ptr<Item> item)
      : tax_rate(1.0 + taxRate), DecoratedItem(std::move(item)) {}
  double price() override { return item().price() * tax_rate; }

 private:
  double tax_rate;
};

void classic_decorator_design_pattern() {
  std::unique_ptr<Item> item1(std::make_unique<Taxed>(
      0.13,
      std::make_unique<Discounted>(0.8, std::make_unique<Book>(10, "cpp"))));

  std::cout << "the price of item1 is " << item1->price() << std::endl;
}
