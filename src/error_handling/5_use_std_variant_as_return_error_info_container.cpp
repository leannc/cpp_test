#include "UseCase.h"
#include <system_error>
#include <variant>

/**
 * NOTE: 1.std::error_code类型，是C++提供的一个公共错误类，它接受一个int错误码和一个std::error_category。
 * NOTE: 2.通过继承std::error_category，实现了自定义的类login_error_category。
 * NOTE: 3.通过定义enum class login_error，得到了自定义的错误码， enum class是强类型，不能被隐式转化为int，这样做的好处，是能保证安全
 * NOTE: 4.利用C++的ADL机制，编写一个与库函数同名的make_errror_code(int val)，来实现参与库函数的重载，让外部调用变得简单。
 */

//NOTE:使用enum class，表示是一个强类型，不能隐式转化为int
enum class login_error_2 {
    success =0,
    invalid_input,
    out_of_range,
    password_error
};


//NOTE: 继承std::error_category，实现了自定义的类LoginErrorCategory。
//NOTE: 单例模式，并且有自定义对象类型，就这样写
auto const& login_error_category_2() {
     const static struct : public std::error_category {
        virtual std::string message(int val) const override {
            switch((login_error_2)val)
            {
                case login_error_2::success:
                    return "Success";
                case login_error_2::invalid_input:
                    return "Invalid input";
                case login_error_2::out_of_range:
                    return "Out of range";
                case login_error_2::password_error:
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


std::error_code make_error_code(login_error_2 ec) {
    return std::error_code((int)ec,login_error_category_2());
}



std::variant<int,std::error_code> login_custom_errocode_std_variant(int x) 
{
    if(x<0) 
    {
        return make_error_code(login_error_2::invalid_input);
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