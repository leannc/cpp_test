//
// Created by kang on 2024/7/28.
//
#include "concurrencpp/concurrencpp.h"

#include <queue>
#include <iostream>

using namespace concurrencpp;

class concurrent_queue {

private:
    async_lock _lock;
    async_condition_variable _cv;
    std::queue<int> _queue;
    bool _abort = false;

public:
    concurrent_queue() = default;

    result<void> shutdown(std::shared_ptr<executor> resume_executor) {
        {
            auto guard = co_await _lock.lock(resume_executor);
            _abort = true;
        }

        _cv.notify_all();
    }

    lazy_result<void> push(std::shared_ptr<executor> resume_executor, int i) {
        {
            auto guard = co_await _lock.lock(resume_executor);
            _queue.push(i);
        }

        _cv.notify_one();
    }

    lazy_result<int> pop(std::shared_ptr<executor> resume_executor) {
        auto guard = co_await _lock.lock(resume_executor);
        co_await _cv.await(resume_executor, guard, [this] {
//            return _abort || !_queue.empty();
            return true;
        });

        if (!_queue.empty()) {
            auto result = _queue.front();
            _queue.pop();

            co_return result;
        }
//
//        assert(_abort);
//        throw std::runtime_error("queue has been shut down.");
        std::cout <<"consumer still working" << std::endl;
        co_return 0;
    }
};

result<void> producer_loop(executor_tag,
                           std::shared_ptr<thread_pool_executor> tpe,
                           concurrent_queue& queue,
                           int range_start,
                           int range_end) {
    for (; range_start < range_end; ++range_start) {
        co_await queue.push(tpe, range_start);
    }
}

result<void> consumer_loop(executor_tag, std::shared_ptr<thread_pool_executor> tpe, concurrent_queue& queue) {
    try {
        while (true) {
            std::cout << co_await queue.pop(tpe) << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}

int async_condition_variable() {
    runtime runtime;
    const auto thread_pool_executor = runtime.thread_pool_executor();
    concurrent_queue queue;

    result<void> producers[4];
    result<void> consumers[4];

    for (int i = 0; i < 4; i++) {
        producers[i] = producer_loop({}, thread_pool_executor, queue, i * 5, (i + 1) * 5);
    }

    for (int i = 0; i < 4; i++) {
        consumers[i] = consumer_loop({}, thread_pool_executor, queue);
    }

    for (int i = 0; i < 4; i++) {
        producers[i].get();
    }

    queue.shutdown(thread_pool_executor).get();

    for (int i = 0; i < 4; i++) {
        consumers[i].get();
    }

    return 0;
}