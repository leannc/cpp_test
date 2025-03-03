#include "UseCase.h"
/**
 * 在lambda表达式里面，实现闭包的方式
 * 1. 值引用，或者设定内部变量名&初始化
 * 2. 设置lambda表达式为mutable
 * 3. 如果需要多个闭包的对象，就用函数对象，就不用lambda
 */

void lambda_closure() {
  auto add = [inner_init = 0](int a) mutable {  // 这个inner_init就是闭包的参数
    inner_init += a;
    return inner_init;
  };
  std::cout << add(1) << std::endl;
  std::cout << add(2) << std::endl;
}
