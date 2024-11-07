//
// Created by kang on 2024/11/7.
//

#include "UseCase.h"

/**
 * std::decay_t 可以把一些包装性质的类型全部去掉，只留下最基本的类型，用于判断，例如
 * */

template <typename T>
auto func_T(T const &t) {
    if constexpr (std::is_same_v<T,int>) {
        return "func_T type matched";
    } else {
        return "func_T type not matched";
    }
}

template <typename T>
auto func_decltyp(T const &t) {
    if constexpr (std::is_same_v<decltype(t),int>) {
        return "func_decltyp type matched";
    } else {
        return "func_decltyp type not matched";
    }
}


/**
 * 效果一样，只不过是用了decltype
 * */
template <typename T>
auto func_decay_t(T const &t) {
    if constexpr (std::is_same_v<std::decay_t<decltype(t)>,int>) {
        return "--func_decay_t type matched";
    } else {
        return "--func_decay_t type not matched";
    }
}


void std_decay_t()
{
    int i=0;
    std::cout<<func_T(i) << std::endl;
    std::cout<<func_decltyp(i) << std::endl;
    std::cout<<func_decay_t(i) << std::endl;

    std::cout<<"--------------"<<std::endl;

    std::string s= "kang";
    std::cout<<func_T(s) << std::endl;
    std::cout<<func_decltyp(s) << std::endl;
    std::cout<<func_decay_t(s) << std::endl;

    std::cout<<"--------------"<<std::endl;

    int test_int =0;
    const int test_const_int =1;
    const int& test_const_int_ref =test_const_int;
    const int* test_const_int_pointer =&test_const_int;
    int* test_int_pointer =&test_int;
    int test_int_array[5];


    static_assert(std::is_same_v<decltype(test_int),int> ,"int is not an int");
    static_assert(std::is_same_v<std::decay_t<decltype(test_int)>,int> ,"int is not an int");

   /**全部不行，静态检查不通过，这些都不能被推断*/
//    static_assert(std::is_same_v<decltype(test_const_int),int> ,"const_int is not an int");
//    static_assert(std::is_same_v<decltype(test_const_int_ref),int> ,"const_int_ref is not an int");

    /**std::decay_t版本的可以*/
    static_assert(std::is_same_v<std::decay_t<decltype(test_const_int)>,int> ,"const_int is not an int");
    static_assert(std::is_same_v<std::decay_t<decltype(test_const_int_ref)>,int> ,"const_int_ref is not an int");

    /**引用的全部不行，静态检查不通过，这些都不能被推断*/
    //    static_assert(std::is_same_v<decltype(test_const_int_pointer),int> ,"const_int_pointer is not an int");
//    static_assert(std::is_same_v<decltype(test_int_pointer),int> ,"int_pointer is not an int");
//    static_assert(std::is_same_v<decltype(test_int_array),int> ,"int_array is not an int");

//    static_assert(std::is_same_ref<std::decay_t<decltype(test_const_int_pointer)>,int> ,"const_int_pointer is not an int");
//    static_assert(std::is_same_v<std::decay_t<decltype(test_int_pointer)>,int> ,"int_pointer is not an int");
//    static_assert(std::is_same_v<std::decay_t<decltype(test_int_array)>,int> ,"int_array is not an int");


}