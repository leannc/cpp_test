#include "UseCase.h"
#include "error_code/login_error_code.h"
#include <variant>



std::variant<int,std::error_code> login_custom_errocode_std_variant(int x) 
{
    if(x<0) 
    {
        return make_error_code(login_error::invalid_input);
    }

    if(x == 4)
    {
        return make_error_code(std::errc::address_in_use);
    }

    for (int i=0; ;i++) {
        if (i*i>=x) {
            return i;
        }
    }
}





void use_std_variant_as_return_error_info_container()
{   
    auto ret = login_custom_errocode_std_variant(-4);
    if (ret.index() != 0 ) {
        std::cout << get<1>(ret).message() << std::endl;  //---- 这里ec.message() 其实就是调用了 ec.category().message(ec.value());是一个简化的写法
    } else {
        std::cout<<"sqrt result is" << get<0>(ret)<<std::endl;
    }

    ret = login_custom_errocode_std_variant(4);
    if (ret.index() != 0 ) {
        std::cout << get<1>(ret).message() << std::endl;  //---- 这里ec.message() 其实就是调用了 ec.category().message(ec.value());是一个简化的写法
    } else {
        std::cout<<"sqrt result is" << get<0>(ret)<<std::endl;
    }

}