//
// Created by kang on 2024/10/9.
//

#include "UseCase.h"
#include "template_classes/HideImplementationTemplate.h"

void hide_implementation_template_use() {
  HideImplementationTemplate<float> float_tmp;
  float_tmp.setValue(16.6);
  std::cout << float_tmp.getValue() << std::endl;

  HideImplementationTemplate<std::string> string_tmp;
  string_tmp.setValue("this is a string");
  std::cout << string_tmp.getValue() << std::endl;

  /// error,因为模板中没有显式实例化 bool
  //    HideImplementationTemplate<bool> bool_tmp;
  //    bool_tmp.setValue(false);
  //    std::cout<<bool_tmp.getValue()<<std::endl;

  /// error,只允许有一个模板
  //    HideImplementationTemplate<float,int> var_tmp;
}
