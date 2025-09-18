//
// Created by kang on 2024/2/4.
//

/**
 *Condition Variable 使用流程
-------------
公共变量
-------------
 1. 创建一个互斥锁(std::mutex)
 2. 创建一个条件变量(std::condition_variable)
 3. 关键！创建一个bool类型的变量，表示条件是否满足，例如done = false;

--------------
Notify 线程
--------------
 1. 创建一个unique_lock，锁住公共的互斥锁(std::mutex)
 2. 做相关的关键区动作
 3. 关键！ 修改表示条件的变量的状态，例如done = true;
 4. 通知等待的线程，使用condition_variable::notify_one()或notify_all() 

--------------
Wait 线程
--------------
 1. 创建一个unique_lock，锁住公共的互斥锁(std::mutex)
 2. 使用condition_variable的wait(unique_lock,lambda)方法等待条件满足
    - 这个方法会自动释放锁，并在被通知后重新获取锁，并根据后面的lambda判断是否继续等待
 */

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

void consume(std::condition_variable* cv, std::mutex* mylock, bool* empty) {
  std::cout << "in consumer" << std::endl;

  std::unique_lock<std::mutex> ul(*mylock);
  // while (*empty) {
  //   // 这个地方，会自己把ul这一把锁释放掉，然后等待，当cv->notify_one()的时候，会重新获取这把锁
  //   cv->wait(ul);
  // }

  // 这个方式，比上面的while方式更好，因为它会在条件变量被通知时重新检查条件。
  cv->wait(ul, [&empty]() { return *empty == false; });
  std::cout << "comsumed" << std::endl;
}

void produce(std::condition_variable* cv, std::mutex* mylock, bool* empty) {
  std::cout << "in producer" << std::endl;

  std::unique_lock<std::mutex> ul(*mylock);
  if (*empty) {
    std::cout << "producing" << std::endl;
    //这个empty=false是核心，就是在lock的critical section中修改了empty的值，这个是为后面判断wait提供的关键跳出点。
    *empty = false;
    // 这个地方，会通知一个等待的线程，这个地方是随机的
    // 这里也可以使用cv->notify_all();来通知所有等待的线程
    cv->notify_one();
    std::cout << "produced" << std::endl;
  }
}

void condition_variable_test() {
  std::mutex lock;
  bool empty = true;
  std::condition_variable cv;

  std::thread consumer(consume, &cv, &lock, &empty);
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  std::thread producer(produce, &cv, &lock, &empty);

  //////////////////////////
  std::cout << "--------------------------------" << std::endl;
  std::thread producer2(produce, &cv, &lock, &empty);
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  std::thread consumer2(consume, &cv, &lock, &empty);

  consumer.join();
  producer.join();

  consumer2.join();
  producer2.join();
}
