//
// Created by kang on 2024/2/4.
//

#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>


void consume(std::condition_variable* cv ,std::mutex* mylock,bool* empty)
{
    std::cout << "in consumer"<<std::endl;

    std::unique_lock<std::mutex> ul(*mylock);
    while (*empty)
    {
        //这个地方，会自己把ul这一把锁释放掉，然后等待，当cv->notify_one()的时候，会重新获取这把锁
        cv->wait(ul);
    }

    std::cout << "comsumed"<<std::endl;
}

void produce(std::condition_variable* cv,std::mutex* mylock,bool* empty)
{
    std::cout << "in producer"<<std::endl;

    std::unique_lock<std::mutex> ul(*mylock);
    if (*empty)
    {
        std::cout << "produced"<<std::endl;
        *empty=false;
        //这个地方，会通知一个等待的线程，这个地方是随机的
        //这里也可以使用cv->notify_all();来通知所有等待的线程
        cv->notify_one();
    }
}

void condition_variable_test()
{
    std::mutex lock;
    bool empty=true;
    std::condition_variable cv;


    std::thread consumer(consume,&cv,&lock,&empty);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::thread producer(produce,&cv,&lock,&empty);

//////////////////////////
    std::cout << "--------------------------------"<<std::endl;
    std::thread producer2(produce,&cv,&lock,&empty);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::thread consumer2(consume,&cv,&lock,&empty);


    consumer.join();
    producer.join();

    consumer2.join();
    producer2.join();

}