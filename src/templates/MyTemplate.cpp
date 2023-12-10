//
// Created by kang on 2023/11/27.
//

#include "MyTemplate.h"
#include <iostream>


template <typename T>
T MyTemplate<T>::getValue() {
    std::cout<< "MyTemplate "<<this->t << std::endl;
    return this->t;
}

// 显式实例化模板
template class MyTemplate<int>;  // 在这里实例化特定类型的模板
template class MyTemplate<double>;  // 在这里实例化特定类型的模板