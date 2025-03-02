//
// Created by kang on 2023/11/27.
//

#include "HideImplementationTemplate.h"
#include <iostream>

/*
 * 直接在CPP里面，以这种形式做实现，然后在底下显式实例化模板，就可以达到隐藏实现的效果了
 * */
template <typename T>
T HideImplementationTemplate<T>::getValue() {
  std::cout << "[HideImplementationTemplate]::getValue(), value: " << this->t << std::endl;
  return this->t;
}

template <typename T>
void HideImplementationTemplate<T>::setValue(T value) {
  std::cout << "[HideImplementationTemplate]::setValue(), the value is set to " << value << std::endl;
  t = value;
}

// 显式实例化模板
template class HideImplementationTemplate<int>;          // 在这里实例化特定类型的模板
template class HideImplementationTemplate<double>;       // 在这里实例化特定类型的模板
template class HideImplementationTemplate<float>;        // 在这里实例化特定类型的模板
template class HideImplementationTemplate<std::string>;  // 在这里实例化特定类型的模板
