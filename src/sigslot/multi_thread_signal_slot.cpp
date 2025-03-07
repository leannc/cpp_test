#include <sigslot/signal.hpp>

void print() { std::cout << "I am in thread : " << std::this_thread::get_id() << std::endl; }

void time_consuming_print() {
  std::cout << "start time consuming print in thread : " << std::this_thread::get_id() << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(2));
  std::cout << "end time consuming print in thread : " << std::this_thread::get_id() << std::endl;
}

void multi_thread_signal_slot() {
  sigslot::signal<> sig;
  print();
  sig.connect(print);
  sig();

  std::cout << std::endl;

  std::thread thread1([&sig]() {
    print();
    sig();
  });

  std::cout << std::endl;

  std::thread thread2([]() {
    sigslot::signal<> sig;
    sig.connect(time_consuming_print);
    sig();  // 这里会阻塞线程，因为 time_consuming_print 是耗时操作

    print();
  });

  thread1.join();
  thread2.join();

  sig();
}
