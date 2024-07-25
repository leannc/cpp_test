//
// Created by kang on 2024/7/24.
//

#include "UseCase.h"

int concurrencpp_hello_world() {
    concurrencpp::runtime runtime;
    auto result = runtime.thread_executor()->submit([] {
        std::cout << "hello world" << std::endl;
    });

    result.get();
    return 0;
}