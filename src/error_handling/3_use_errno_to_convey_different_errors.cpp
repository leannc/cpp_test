#include "UseCase.h"
#include <errno.h>
/**
 * NOTE:使用errno，时posix的标准方式，是需要依赖errno全局变量的。
 * NOTE:perror是一个便捷的打印功能。
 */

int mysqrt_errno(int x) 
{
    if(x<0) 
    {
        errno = EDOM;
        return -1;
    }

    if(x == 4)
    {
        errno =EINVAL;
        return -1;
    }

    for (int i=0; ;i++) {
        if (i*i>=x) {
            return i;
        }
    }
}





void use_errno_to_convey_different_errors()
{   
    int ret = mysqrt_errno(-4);
    if (ret ==-1) {
        perror("sqrt error reson");
    } else {
        std::cout<<"sqrt result is" << ret<<std::endl;
    }
}