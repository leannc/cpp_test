//
// Created by kang on 2024/7/24.
//
#include "UseCase.h"

// using namespace concurrencpp;
using namespace std::chrono_literals;  //NOLINT

std::vector<int> make_random_vector() {
  std::vector<int> vec(64 * 1'024);

  std::srand(std::time(nullptr));
  for (auto& i : vec) {
    i = ::rand();
  }

  return vec;
}

concurrencpp::result<size_t> count_even(std::shared_ptr<concurrencpp::thread_pool_executor> tpe,
                                        std::shared_ptr<concurrencpp::timer_queue> tq, const std::vector<int>& vector,
                                        int& worker_times) {  //NOLINT
  std::cout << "begin count_even in thread : " << std::this_thread::get_id() << std::endl;
  //    co_await concurrencpp::resume_on(tpe);
  //    co_await tq->make_delay_object(1ms, tpe);
  std::cout << "resume count_even in thread : " << std::this_thread::get_id() << std::endl;
  const auto vecor_size = vector.size();
  const auto concurrency_level = tpe->max_concurrency_level();
  std::cout << "concurrency_level: " << concurrency_level << std::endl;
  const auto chunk_size = vecor_size / concurrency_level;
  //    co_await concurrencpp::resume_on(tpe);
  //    std::cout << "returned: " << concurrency_level << std::endl;
  std::vector<concurrencpp::result<size_t>> chunk_count;

  for (auto i = 0; i < concurrency_level; i++) {
    const auto chunk_begin = i * chunk_size;
    const auto chunk_end = chunk_begin + chunk_size;
    auto result = tpe->submit([&vector, chunk_begin, chunk_end, &worker_times]() -> size_t {
      worker_times++;
      std::this_thread::sleep_for(100ms);
      //            std::cout << "start work : " << std::this_thread::get_id()<< std::endl;
      return std::count_if(vector.begin() + chunk_begin, vector.begin() + chunk_end, [](auto i) { return i % 2 == 0; });
    });

    chunk_count.emplace_back(std::move(result));
  }

  size_t total_count = 0;
  for (auto& result : chunk_count) {
    std::cout << "before co_await,total_count : " << total_count << std::endl;
    total_count += co_await result;
    //        total_count += result.get();
    std::cout << "after co_await total_count: " << total_count << std::endl;
  }

  std::cout << "end count_even in thread : " << std::this_thread::get_id() << std::endl;
  co_return total_count;
}

int concurrencpp_even_number_counting() {
  int thread_invoke_times = 0;
  int thread_terminate_times = 0;
  int worker_invoke_times = 0;
  concurrencpp::runtime_options options;
  options.thread_started_callback = [&](std::string_view thread_name) {
    thread_invoke_times++;
    //        std::cout << "A new thread is starting to run, name: " << thread_name << ", thread id: " <<
    //        std::this_thread::get_id()
    //                  << std::endl;
  };

  options.thread_terminated_callback = [&](std::string_view thread_name) {
    thread_terminate_times++;
    //        std::cout << "A thread is terminating, name: " << thread_name << ", thread id: " <<
    //        std::this_thread::get_id() << std::endl;
  };

  concurrencpp::runtime runtime(options);
  const auto vector = make_random_vector();
  std::cout << "before calling count_even  in thread : " << std::this_thread::get_id() << std::endl;
  auto result = count_even(runtime.thread_pool_executor(), runtime.timer_queue(), vector, worker_invoke_times);
  //    auto result2 = count_even(runtime.thread_pool_executor(), vector,worker_invoke_times);
  //    auto result3 = count_even(runtime.thread_pool_executor(), vector,worker_invoke_times);
  //    auto result4 = count_even(runtime.thread_pool_executor(), vector,worker_invoke_times);
  //    auto result5 = count_even(runtime.thread_pool_executor(), vector,worker_invoke_times);
  std::cout << "after calling count_even  in thread : " << std::this_thread::get_id() << std::endl;
  //    const auto total_count = result.get();
  const auto total_count = result.get();
  //    const auto total_count2 = result2.get();
  std::cout << "thread_invoke_times : " << thread_invoke_times << std::endl;
  std::cout << "thread_terminate_times : " << thread_terminate_times << std::endl;
  std::cout << "worker_invoke_times : " << worker_invoke_times << std::endl;
  std::cout << "there are " << total_count << " even numbers in the vector" << std::endl;
  return 0;
}
