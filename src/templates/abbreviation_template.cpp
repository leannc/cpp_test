//
// Created by kang on 2024/10/10.
//

#include "UseCase.h"

auto shout(auto arg)
{
    std::cout<<arg<<std::endl;
}

auto shout2(auto...args)
{
    ((std::cout<<"fold expression: "<<args<<", "),...)<<std::endl;
}



void abbreviation_template()
{
    shout(1);
    shout("kang");
    shout<double>(4.2);


    shout2(1);
    shout2("wang");
    shout2<double>(4.2);

    shout2(1,false,"kang");
}