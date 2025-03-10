//
// Created by kang on 2024/7/26.
//
#include <iostream>

#include "concurrencpp/concurrencpp.h"

using namespace std::chrono_literals;

int oneshot_timer() {
  concurrencpp::runtime runtime;
  concurrencpp::timer timer = runtime.timer_queue()->make_one_shot_timer(
      3s, runtime.thread_executor(), [] { std::cout << "hello and goodbye" << std::endl; });

  std::cout << "timer due time (ms): " << timer.get_due_time().count() << std::endl;
  std::cout << "timer frequency (ms): " << timer.get_frequency().count() << std::endl;
  std::cout << "timer-associated executor : " << timer.get_executor()->name << std::endl;

  std::this_thread::sleep_for(4s);
  return 0;
}
