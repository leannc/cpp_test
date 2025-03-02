//
// Created by kang on 2024/11/9.
//

#include "UseCase.h"

class StealConstructionParam {
 public:
  StealConstructionParam(
      std::string value_, std::string &reference_, const std::string &const_reference_,
      std::string &&lvalue_to_rvalue_reference_,
      const std::string &rvalue_to_const_reference_  /// 这个地方，如果想要外面直接传rvalue，那就必须是用const
                                                     /// &,否则编译无法通过。
      )
      : value(std::move(value_)), reference(std::move(reference_)), const_reference_ref(std::move(const_reference_)),
        lvalue_to_rvalue_reference(std::move(lvalue_to_rvalue_reference_)),
        rvalue_to_const_reference(std::move(rvalue_to_const_reference_)) {}

 public:
  std::string value;
  std::string reference;
  std::string const_reference_ref;
  std::string lvalue_to_rvalue_reference;
  std::string rvalue_to_const_reference;
};

void std_move() {
  std::string value = "still valid";
  std::string reference = "still valid";
  std::string const_reference = "still valid";
  std::string lvalue_to_rvalue_reference = "still valid";

  StealConstructionParam stealer(value, reference, const_reference, std::move(lvalue_to_rvalue_reference),
                                 "rvalue valid");

  std::cout << "[outside] value : " << value << std::endl;
  std::cout << "[outside] reference : " << reference << std::endl;
  std::cout << "[outside] const reference : " << const_reference << std::endl;
  std::cout << "[outside] lvalue_to_rvalue_reference : " << lvalue_to_rvalue_reference << std::endl;

  std::cout << "-----------------------------" << std::endl;

  //    std::cout<<"[stealer]  value : "<<stealer.value<<std::endl;
  //    std::cout<<"[stealer]  reference : "<<stealer.reference<<std::endl;
  //    std::cout<<"[stealer]  const reference : "<<stealer.const_reference_ref<<std::endl;
  //    std::cout<<"[stealer]  lvalue_to_rvalue_reference : "<<stealer.lvalue_to_rvalue_reference<<std::endl;
  //    std::cout<<"[stealer]  rvalue to const reference : "<<stealer.rvalue_to_const_reference<<std::endl;
}
