//
// Created by kang on 2024/2/4.
//

#include <iostream>
#include <thread>
#include <mutex>
#include <semaphore>
#include <vector>

#define MAX_SPACE 30

std::vector<int> queue;


sem_t availabe_data;
sem_t available_space;

std::mutex lock;

void produce()
{
    while(true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        sem_wait(&available_space);
        std::lock_guard<std::mutex> g(lock);
        queue.push_back(1);
        std::cout << "produced,remain: "<<queue.size()<<std::endl;
        sem_post(&availabe_data);
    }
}


void consume()
{

    while (true)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(70));
        sem_wait(&availabe_data);
        std::lock_guard<std::mutex> g(lock);
        queue.pop_back();
        std::cout << "consumed,remain: "<<queue.size()<<std::endl;
        sem_post(&available_space);
    }

}


int semaphore_test()
{
    sem_init(&availabe_data,1,0);
    sem_init(&available_space,1,MAX_SPACE);


    std::thread producer(produce);
    std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    std::thread consumer(consume);


    producer.join();
    consumer.join();
    return 0;
}