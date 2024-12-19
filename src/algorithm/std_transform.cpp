//
// Created by kang on 2024/12/19.
//


#include "UseCase.h"


void std_transform()
{
    std::vector<int> v(10);
    std::iota(std::begin(v),std::end(v),1);


    ///所有的成员值+1，并存入到一个新的vector中
    std::vector<int> dest;
    std::transform(std::begin(v),std::end(v),std::back_inserter(dest),[](int i) {return i+1;});

    std::cout<<"add 1 to all the members, and save in a new vector"<<std::endl;
    for (int i : dest)  {std::cout<<i<<std::endl;}  ///2 3 4 5 6 7 8 9 10 11
    std::cout<<"==================================================="<<std::endl;

    std::string s{"abcdefghijklmnopqrstuvwxyz1234567890"};



    ///把两个vector的元素，parawise地组合在一起
    std::vector<std::string> dest_str;
    assert(std::size(s)>=std::size(v));  ///第二个container的长度，一定要大于第一个，否则运行时会报错。
    std::transform(std::begin(v),std::end(v),std::begin(s),std::back_inserter(dest_str),[](int i,char c) {return std::to_string(i) +std::string(1,c);});

    std::cout<<"add a int and string"<<std::endl;
    for (auto item : dest_str)  {std::cout<<item<<std::endl;}  ///1a 2b 3c 4d 5e 6f 7g 8h 9i 10j
    std::cout<<"==================================================="<<std::endl;


    ///直接修改现有的vector
    std::transform(std::begin(v),std::end(v),std::begin(s),std::begin(v),[](int i,char c) {return i+c;});
    std::cout<<"modify origin vector"<<std::endl;
    for (auto item : v)  {std::cout<<item<<std::endl;}  ///98 100 102 104 106 108 110 112 114 116
    std::cout<<"==================================================="<<std::endl;
}