//
// Created by kang on 2023/11/21.
//

#pragma once

#include <string>
#include <iostream>

void header(const std::string title)
{
    std::cout<<"++++++++++++++++++[START {0}]+++++++++++++++++++++++++++++++"<<title<<std::endl;
}

void footer(const std::string title)
{
    std::cout<<"------------------[END {0}]-------------------------------"<<title<<std::endl;
}

#define CALL_USE_CASE(func) \
    header(#func);\
    func();\
//    footer(#func);