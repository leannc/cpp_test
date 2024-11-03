//
// Created by kang on 2024/11/3.
//
#include "UseCase.h"

#include <span>
#include <array>

void print(std::span<int> s)
{
    std::for_each(s.begin(),s.end(),[](int element){
        std::cout<<element<<",";
    });
    std::cout<<std::endl;
}


void std_span()
{
    std::vector<int> v{1,2,3,4,5,6};
    std::cout<<"----------std::vector---------"<<std::endl;
    print(v);

    std::array<int,3> arr = {10,20,30};
    std::cout<<"----------std::array---------"<<std::endl;
    print(arr);

    int raw_array[3]={110,210,310};
    std::cout<<"----------raw array---------"<<std::endl;
    print(raw_array);

    std::span s = v; ///这个地方非常cheap，因为s就只是一个 指针+长度 而已
    std::cout<<"----------std span---------"<<std::endl;
    print(s);
    std::cout<<s.size()<<std::endl;

}