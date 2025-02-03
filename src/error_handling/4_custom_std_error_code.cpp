#include "UseCase.h"
#include <system_error>

/**
 * NOTE: 1.std::error_code类型，是C++提供的一个公共错误类，它接受一个int错误码和一个std::error_category。
 * NOTE: 2.通过继承std::error_category，实现了自定义的类login_error_category。
 * NOTE: 3.通过定义enum class login_error，得到了自定义的错误码， enum class是强类型，不能被隐式转化为int，这样做的好处，是能保证安全
 * NOTE: 4.利用C++的ADL机制，编写一个与库函数同名的make_errror_code(int val)，来实现参与库函数的重载，让外部调用变得简单。
 */

//NOTE:使用enum class，表示是一个强类型，不能隐式转化为int
enum class login_error {
    success =0,
    invalid_input,
    out_of_range,
    password_error
};


//NOTE: 继承std::error_category，实现了自定义的类LoginErrorCategory。
//NOTE: 单例模式，并且有自定义对象类型，就这样写
auto const& login_error_category() {
     const static struct : public std::error_category {
        virtual std::string message(int val) const override {
            switch((login_error)val)
            {
                case login_error::success:
                    return "Success";
                case login_error::invalid_input:
                    return "Invalid input";
                case login_error::out_of_range:
                    return "Out of range";
                case login_error::password_error:
                    return "Password error";
                default:
                    return "Unknown error";
            }
        }
    
        virtual const char* name() const noexcept override {
            return "login_error";
        };
    } instance;
    // static const LoginErrorCategory instance;
    return instance;
}


std::error_code make_error_code(login_error ec) {
    return std::error_code((int)ec,login_error_category());
}



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