#include "UseCase.h"
#include <optional>

/**
 * NOTE:使用optional时，只能处理失败只有一种情况的场景，如果有多种错误，这个就没法表达了
 */

std::optional<int> mysqrt_optional(int x) 
{
    if(x<0) 
    {
        return std::nullopt;
    }

    for (int i=0; ;i++) {
        if (i*i>=x) {
            return i;
        }
    }
}



void use_optional_to_convey_error_info()
{
    auto ret = mysqrt_optional(-4);
    if (ret) {
        std::cout<<"sqrt result is" << *ret<<std::endl;
    } else {
        std::cout<<"sqrt's param should greater than zero."<<std::endl;
    }
}