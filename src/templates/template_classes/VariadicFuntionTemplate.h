//
// Created by kang on 2024/10/9.
//

#ifndef CPP_TEST_VARIADICFUNTIONTEMPLATE_H
#define CPP_TEST_VARIADICFUNTIONTEMPLATE_H

#include <iostream>

template<class ...CLASS>
void f_class(CLASS... args) {};

template<typename ...TYPES>
void f_typename(TYPES... args) {};


template<typename  T>
void shout(T value) {
    std::cout<<"the value is "<<value<<std::endl;
}

template<typename T,typename ...Ts>
void shout(T value, Ts... args)
{
    std::cout<<"multy pack :" <<value<<std::endl;
    shout(args...);
};

///在variadic function template中，是可以把parameter pack放在前面的，后面可以自动推导。但是在 variadic class template中就不行， parameter pack必须放最后面。
template<typename ..., typename U,typename=void> ///也可以有默认值
void valid(U,...) {};


template<typename ...Ts, typename U,typename=void> ///也可以有默认值
void invalid(Ts...,U) {}; ///这个是不行的，不能被推导，调用就会报错，因为它的parameter pack放前面了

#endif //CPP_TEST_VARIADICFUNTIONTEMPLATE_H
