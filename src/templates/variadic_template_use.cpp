//
// Created by kang on 2024/10/9.
//
#include "UseCase.h"
#include "template_classes/VariadicClassTemplate.h"


void variadic_template_use()
{
    VariadicStruct<> s0;
    VariadicStruct<int> s1;
    VariadicStruct<int,double> s2;

    VariadicClass<> c0;
    VariadicClass<float> c1;
    VariadicClass<float,int,std::string> c2;


    std::cout<<"succeed"<<std::endl;
}