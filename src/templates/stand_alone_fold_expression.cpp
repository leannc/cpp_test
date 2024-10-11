//
// Created by kang on 2024/10/10.
//
#include "UseCase.h"

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