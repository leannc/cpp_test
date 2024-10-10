//
// Created by kang on 2024/10/9.
//

#include "VariadicFuntionTemplate.h"


void variadic_function_template() {
    f_class();
    f_class(1,2);
    valid(1.0,1,2,3);

    //invalid(1.0,1,2,3);  ///error,不能被推导，因为这个函数的签名，的parameter pack在前面
    shout(1,2,"abc");
}

