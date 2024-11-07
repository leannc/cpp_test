//
// Created by kang on 2024/11/7.
//

#include "UseCase.h"

/**
 * std::is_same_v就是用来判断是否是同样的类型。这里的v，代表的type的value
 * 在模板中，直接使用std::is_same_v<T,int> 就可以在编译时判断，传入的这个模板参数是否是int类型，则方便我们写模板逻辑。
 * 这里需要用if constexpr来做，否则会报错。
 * */

template <typename T>
auto func(T t) {
    if constexpr (std::is_same_v<T,int>) {
        return t+1;
    } else {
        return t.substr(1);
    }
}

/**
 * 效果一样，只不过是用了decltype
 * */
template <typename T>
auto func2(T t) {
    if constexpr (std::is_same_v<decltype(t),int>) {
        return t+2;
    } else {
        return t.substr(2);
    }
}


void std_is_same_v()
{
    int i=0;
    std::cout<<func(i) << std::endl;
    std::cout<<func2(i) << std::endl;

    std::string s= "kang";
    std::cout<<func(s) << std::endl;
    std::cout<<func2(s) << std::endl;



}