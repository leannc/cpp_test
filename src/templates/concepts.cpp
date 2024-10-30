//
// Created by kang on 2024/10/30.
//

#include "UseCase.h"

template<typename T>
concept floating_value = std::is_floating_point_v<T>;

template<typename T>
concept any_number = std::is_floating_point_v<T> || std::is_integral_v<T>;


template<floating_value F>
F sum1 (F v1,F v2)
{
    std::cout<<"in ordinary mode sum1 : "<<v1 + v2<<std::endl;

    return v1+v2;
}



floating_value auto sum2 (floating_value auto v1, floating_value auto v2)
{
    std::cout<<"in auto mode sum2 : "<<v1 + v2<<std::endl;

    return v1+v2;
}


any_number auto sum3 (any_number auto v1, any_number auto v2)
{
    std::cout<<"in any auto mode sum3 : "<<v1 + v2<<std::endl;

    return v1+v2;
}



void concept_test()
{
    sum1(2.3,4.5);
//    sum1(2.3,4.5f);   ///报错，因为两者的类型不一样，一个是double，一个是float
//    sum1(1,2.0);   ///报错，因为1是整数，不满足floating_value的要求

    sum2(2.1,5.3);
    sum2(2.3,5.3f);  ///可以，因为两个参数都满足 floating_value的要求
//    sum2(2.3,5);  ///报错，因为5是整数，不满足floating_value的要求

    sum3(2.3,5);  ///可以，因为any_number 的 concept支持float 或者 integral 。



}