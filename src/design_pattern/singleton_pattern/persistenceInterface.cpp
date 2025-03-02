//
// Created by kang on 2024/11/12.
//

#include "database.h"

PersistenceInterface *instance = nullptr;

PersistenceInterface *get_persistence_interface() {
  static bool init = []() {
    if (!instance) {
      static Database db;
      instance = &db;
    }
    return true;
  }();

  return instance;
}

void set_persistence_interface(PersistenceInterface *persistence) { instance = persistence; }
