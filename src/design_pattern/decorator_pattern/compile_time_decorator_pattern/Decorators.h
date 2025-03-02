//
// Created by kang on 2024/11/11.
//

#pragma once

#include <concepts>

template <typename T>
concept PricedItem = requires(T item) {
  { item.price() } -> std::same_as<double>;
};

template <double discount, PricedItem Item> class Discounted {
 public:
  template <typename... Args>
  explicit Discounted(Args &&...args) : item_{std::forward<Args>(args)...} {}

  double price() const { return item_.price() * discount; }

 private:
  Item item_;
};

template <double taxRate, PricedItem Item> class Taxed : private Item {
 public:
  template <typename... Args>
  explicit Taxed(Args &&...args) : Item{std::forward<Args>(args)...} {}

  double price() const { return Item::price() * (1.0 + taxRate); }
};
