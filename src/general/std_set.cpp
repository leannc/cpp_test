//
// Created by kang on 2023/12/10.
//
#include <set>
#include <iostream>

void std_set_test()
{
    std::set<int> test_sort_set;

    test_sort_set.insert(1);
    test_sort_set.insert(2);
    test_sort_set.insert(9);
    test_sort_set.insert(4);
    test_sort_set.insert(5);

    ///顺序输出set，这里会被自动排序
    for(auto it = test_sort_set.begin(); it != test_sort_set.end(); it++)
    {
        std::cout<<*it<<std::endl;
    }

    std::cout<<"===================="<<std::endl;

    ///==============string
    std::set<std::string> test_sort_set_string;
    //对string做同样的初始化，最后输出，判断是否排序
    test_sort_set_string.insert("1");
    test_sort_set_string.insert("2");
    test_sort_set_string.insert("9");
    test_sort_set_string.insert("4");
    test_sort_set_string.insert("5");

    ///顺序输出set，这里会被自动排序
    for(auto it = test_sort_set_string.begin(); it != test_sort_set_string.end(); it++)
    {
        std::cout<<*it<<std::endl;
    }

    ///==============string
    std::set<std::string> test_sort_set_string2;
    //对string做同样的初始化，最后输出，判断是否排序
    test_sort_set_string2.insert("a");
    test_sort_set_string2.insert("b");
    test_sort_set_string2.insert("x");
    test_sort_set_string2.insert("e");
    test_sort_set_string2.insert("d");

    std::cout<<"===================="<<std::endl;
    ///顺序输出set，这里会被自动排序
    for(auto it = test_sort_set_string2.begin(); it != test_sort_set_string2.end(); it++)
    {
        std::cout<<*it<<std::endl;
    }
}