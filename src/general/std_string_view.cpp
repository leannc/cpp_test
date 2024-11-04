//
// Created by kang on 2024/11/4.
//

#include "UseCase.h"
#include <string_view>

void print(std::string_view s)
{
    std::cout<<"------the string_view is : "<<s<<", the size is "<<s.size()<<".  the first address is "<<s.data()<<std::endl;
}


void std_string_view()
{
    std::string s("this is a std string");

    std::cout<<"string length is "<<s.size()<<", the first address is "<<s.data() <<std::endl;
    print(s);

    char* c("asdfasdf");
    print(c);




}