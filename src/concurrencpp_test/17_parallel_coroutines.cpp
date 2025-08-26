#include "concurrencpp/concurrencpp.h"
#include <iostream>

using namespace concurrencpp;

int fibonacci_sync(int i) {
  if (i == 0) { return 0; }

  if (i == 1) { return 1; }

  return fibonacci_sync(i - 1) + fibonacci_sync(i - 2);
}

result<int> fibonacci(executor_tag, std::shared_ptr<thread_pool_executor> tpe, const int curr) {
  if (curr <= 10) { co_return fibonacci_sync(curr); }

  auto fib_1 = fibonacci({}, tpe, curr - 1);
  auto fib_2 = fibonacci({}, tpe, curr - 2);

  co_return co_await fib_1 + co_await fib_2;
}

result<int> fibonacci2(std::shared_ptr<thread_pool_executor> tpe, const int curr) {
  co_await concurrencpp::resume_on(tpe);
  if (curr <= 10) { co_return fibonacci_sync(curr); }

  auto fib_1 = fibonacci2(tpe, curr - 1);
  auto fib_2 = fibonacci2(tpe, curr - 2);

  co_return co_await fib_1 + co_await fib_2;
}

int parallel_coroutines() {
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
  //   auto fibb_30 = fibonacci({}, runtime.thread_pool_executor(), 30).get();
  auto fibb_30_2 = fibonacci2(runtime.thread_pool_executor(), 30).get();
  //   std::cout << "fibonacci(30) = " << fibb_30 << std::endl;
  std::cout << "fibonacci(30_2) = " << fibb_30_2 << std::endl;

  std::cout << "【" << std::this_thread::get_id() << "】" << "thread_invoke_times : " << thread_invoke_times
            << std::endl;
  std::cout << "【" << std::this_thread::get_id() << "】" << "thread_terminate_times : " << thread_terminate_times
            << std::endl;
  std::cout << "【" << std::this_thread::get_id() << "】" << "worker_invoke_times : " << worker_invoke_times
            << std::endl;
  return 0;
}
