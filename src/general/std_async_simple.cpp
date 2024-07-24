//
// Created by kang on 2024/2/4.
//

#include <iostream>
#include <future>
#include <thread>

int square(int x,int ms) {
    //打印出当前线程的id
     std::this_thread::sleep_for(std::chrono::milliseconds(ms));
     std::cout << "thread id is " << std::this_thread::get_id() <<", param is "<< x << std::endl;
     return x*x;
 }


 void std_async_simple_test()
 {
     std::cout << "main thread id is " << std::this_thread::get_id() << std::endl;
    //这里会马上开始执行，是在另一个线程中执行的
     std::future<int> f= std::async(&square,12,4000);

     for (int i=0;i<10;i++) {
         std::cout << square(i,0) << std::endl;
     }

     //这里会等待f的结果
     int result = f.get();

     std::cout <<"result is " <<result<< std::endl;
 }