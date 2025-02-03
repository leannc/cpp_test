#include "UseCase.h"
#include "error_code/login_error_code.h"




int login_custom_errocode(int x,std::error_code& ec) 
{
    if(x<0) 
    {
        ec = make_error_code(login_error::invalid_input);
        return -1;
    }

    if(x == 4)
    {
        ec= make_error_code(std::errc::address_in_use);
        return -1;
    }

    for (int i=0; ;i++) {
        if (i*i>=x) {
            return i;
        }
    }
}


void custom_std_error_code()
{   
    std::error_code ec;
    int ret = login_custom_errocode(-4,ec);
    if (ec) {
        std::cout << ec.message() << std::endl;  //---- 这里ec.message() 其实就是调用了 ec.category().message(ec.value());是一个简化的写法
    } else {
        std::cout<<"sqrt result is" << ret<<std::endl;
    }

    ret = login_custom_errocode(4,ec);
    if (ec) {
        std::cout << ec.message() << std::endl;
    } else {
        std::cout<<"sqrt result is" << ret<<std::endl;
    }
}