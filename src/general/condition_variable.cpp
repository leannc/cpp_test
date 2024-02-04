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
        cv->notify_one();
    }
}

int condition_variable_test()
{
    std::mutex lock;
    bool empty=true;
    std::condition_variable cv;


    std::thread consumer(consume,&cv,&lock,&empty);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::thread producer(produce,&cv,&lock,&empty);

    consumer.join();
    producer.join();

    return 0;
}