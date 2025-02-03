//
// Created by kang on 2024/10/10.
//
#include "UseCase.h"

/**
 * NOTE:当参数包(parameter pack)是在函数的参数列表内部展开时，就不用折叠表达式(fold expression)，直接写patern...就可以
 * NOTE:当参数包的展开，是要加上整个函数表达时，就需要用折叠表达式，例如逗号表达式等来处理。
 */

template<typename T>
bool HasComponent()
{
    std::cout<<"has component"<<std::endl;
    return true;
}


template<typename... Component>
static void CopyComponentIfExists(int dst, int src)
{
//    HasComponent<Component>();
    ([&]()
    {
        if (HasComponent<Component>())
        {
//            dst.AddOrReplaceComponent<Component>(src.GetComponent<Component>());
        }
    }(), ...);
}


template<typename ...U>
double Sum(U... args)
{
    return (args+...);
}

template<typename ...T>
void Shout(T... t)
{
    ((std::cout<<t<<", "),...)<<std::endl;
}

template<auto ...T>
void Shout2()
{
    ((std::cout<<T<<", "),...)<<std::endl;
}


void stand_alone_fold_expression_using()
{
    std::cout<<Sum(1,2,3,4,5)<<std::endl;
    Shout(1,2.0,"kang",false);
    Shout2<1,2>();

}