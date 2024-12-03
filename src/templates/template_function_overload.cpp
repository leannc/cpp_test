//
// Created by kang on 2024/12/3.
//

#include "UseCase.h"

template<typename T>
void func(T)
{
    std::cout<<"in generic function"<<std::endl;
}

template<>
void func(int i)
{
    std::cout<<"in int specification function"<<std::endl;
}


///没有generic的float版本，所以在有float版本的时候，会被调用
template<>
void func(float i)
{
    std::cout<<"in float specification function"<<std::endl;
}

///有了这个以后，特化的那个int是不会被执行的
void func(int i)
{
    std::cout<<"in normal int function"<<std::endl;
}

void func(double d)
{
    std::cout<<"in normal double function"<<std::endl;
}

void template_function_overload()
{
    func('a');
    func(32);
    func(0.34);
    func(0.34f);
}