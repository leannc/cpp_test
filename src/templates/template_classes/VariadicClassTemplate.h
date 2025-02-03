//
// Created by kang on 2024/10/9.
//

#ifndef CPP_TEST_VARIADICCLASSTEMPLATE_H
#define CPP_TEST_VARIADICCLASSTEMPLATE_H

template<class...>
struct VariadicStruct {};

template<class... types>
class VariadicClass{};

//----error，variadic class template中，parameter pack必须放在最后
//template< typename ...Ts,typename U> ///也可以有默认值
//class InvalidClass  {};



#endif //CPP_TEST_VARIADICCLASSTEMPLATE_H
