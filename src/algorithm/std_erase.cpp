//
// Created by kang on 2024/11/3.
//
#include "UseCase.h"




void std_erase()
{

    std::vector<int> v{3,5,7,1,4,3,8,4,2,46,2,1};

    std::for_each(v.begin(),v.end(),[](int element){
       std::cout<<element<<"," ;
    });
    std::cout<<std::endl;


    int value = 3;
    std::cout << "------------ after std::erase "<<value<<",the vector is -----------"<<std::endl;
    std::erase(v,value);
    std::for_each(v.begin(),v.end(),[](int element){
        std::cout<<element<<"," ;
    });
    std::cout<<std::endl;
}