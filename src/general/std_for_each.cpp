//
// Created by kang on 2024/11/1.
//
#include "UseCase.h"
#include <execution>



int print(const int& i)
{
    std::cout<<"calling print "<<i<<std::endl;
    return i;
}


void print_v2(const int& i,const int& j)
{
    std::cout<<"calling print "<<i<<","<<j<<std::endl;
}


void std_for_each_test()
{
    std::vector<int> vec;
    for (int i=0;i<10;i++) vec.push_back(i);
    std::for_each(vec.begin(),vec.end(),print);

    std::cout<<"-------------------"<<std::endl;

    std::for_each(std::execution::par,vec.begin(),vec.end(),print);

}