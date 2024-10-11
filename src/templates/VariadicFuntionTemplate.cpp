//
// Created by kang on 2024/10/9.
//

#include <string>
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


void variadic_function_template() {
    f_class();
    f_class(1,2);
    valid(1.0,1,2,3);

    //invalid(1.0,1,2,3);  ///error,不能被推导，因为这个函数的签名，的parameter pack在前面
    shout(1,2,"abc");

//    [](std::string str){
//       std::cout<<str<<std::endl;
//    }("sdfa");
}

