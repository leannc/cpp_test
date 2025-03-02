//
// Created by kang on 2024/11/12.
//

#ifndef CPP_TEST_TEXTFILE_H
#define CPP_TEST_TEXTFILE_H

#include "../UseCase.h"
#include "persistenceInterface.h"

class TextFile : public PersistenceInterface {
 public:
  virtual ~TextFile() = default;
  bool read() const {
    // do something
    do_read();
    return true;
  }

  bool write() {
    // do something
    do_write();
    return true;
  }

 private:
  bool do_read() const override {
    std::cout << "TextFile::do_read()" << std::endl;
    return true;
  };
  bool do_write() override {
    std::cout << "TextFile::do_write()" << std::endl;
    return true;
  };
};

#endif  // CPP_TEST_TEXTFILE_H
