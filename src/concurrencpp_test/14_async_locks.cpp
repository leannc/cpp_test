//
// Created by kang on 2024/7/28.
//
#include "concurrencpp/concurrencpp.h"

#include <vector>
#include <iostream>
#include <algorithm>

std::vector<size_t> numbers;
concurrencpp::async_lock lock;

concurrencpp::result<void> add_numbers(concurrencpp::executor_tag,
                                       std::shared_ptr<concurrencpp::executor> executor,
                                       size_t begin,
                                       size_t end) {
    for (auto i = begin; i < end; i++) {
        std::cout << i << "th before await : " <<std::this_thread::get_id() << std::endl;
        concurrencpp::scoped_async_lock raii_wrapper = co_await lock.lock(executor);
        std::cout << i << "th after await : " <<std::this_thread::get_id() << std::endl;
        numbers.push_back(i);
    }
}

int concurrencpp_async_locks() {
    concurrencpp::runtime runtime;
    constexpr size_t range = 1000;
//    constexpr size_t range = 10'000'000;
    constexpr size_t sections = 4;
    concurrencpp::result<void> results[sections];

    for (size_t i = 0; i < 4; i++) {
        const auto range_start = i * range / sections;
        const auto range_end = (i + 1) * range / sections;

        results[i] = add_numbers({}, runtime.thread_pool_executor(), range_start, range_end);
    }


    std::cout << "task commited" << std::endl;


    for (auto& result : results) {
        result.get();
    }

    std::cout << "vector size is " << numbers.size() << std::endl;

    // make sure the vector state has not been corrupted by unprotected concurrent accesses
    std::sort(numbers.begin(), numbers.end());
    for (size_t i = 0; i < range; i++) {
        if (numbers[i] != i) {
            std::cerr << "vector state is corrupted." << std::endl;
            return -1;
        }
    }

    std::cout << "succeeded pushing range [0 - 10,000,000] concurrently to the vector!" << std::endl;
    return 0;
}