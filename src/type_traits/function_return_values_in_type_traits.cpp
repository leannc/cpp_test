//
// Created by kang on 2024/11/7.
//

#include "UseCase.h"

/**
 * std::is_void_v可以判断值是否是空
 * std::is_integral_v可以判断值是否为整数
 * declval<T>，可以在 unevaluate的情况下，返回一个T类型的对象出来，这里没有真正执行一个对象的构造。
 * */

template <typename F>
auto invoke(F f) {
    if constexpr (std::is_void_v<decltype(f())>) {
        std::cout << "no return value" << std::endl;
    }
    else if constexpr (std::is_integral_v<std::invoke_result_t<F>>) {  ///这个写法的作用，与上面的decltype(f())相同，只不过是换种写法，可以用于没有形参f的场景。
        std::cout << "int return value" << std::endl;
    }
    else if constexpr (std::is_same_v<decltype(std::declval<F>()()),std::string>) {  ///第三种写法，会凭空搞一个默认构造函数，它不求值，只关心返回值类型，只有这里可以这样玩。这个是在没有形参f的情况下，使用的玩法
        std::cout << "string return value" << std::endl;
    }
    else if constexpr (std::is_floating_point_v<decltype(F()())>) {  ///第四种写法，会使用默认构造函数构造一个，也可以不用f，但是lambda里面不能捕获，否则不会创建默认构造函数，这里也就不能用了。
                                                                        ///因为底下有个string是有捕获的，没法生成默认构造函数，所以这种写法不能放到第三种写法的上面，要不然就会在匹配string的时候报错。
        std::cout << "float return value" << std::endl;
    }
    else {
        std::cout<<"default return value is " << f()<<std::endl;
    }
}



void function_return_values_in_type_traits()
{
    invoke([]() -> int{
        return 1;
    });

    invoke([]() {
        return 0.1;
    });

    invoke([&]() ->std::string {
        return "kang";
    });



    invoke([]() {
        std::cout<<"no return"<<std::endl;
    });



}