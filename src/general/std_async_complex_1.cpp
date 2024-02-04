//
// Created by kang on 2024/2/4.
//

#include <iostream>
#include <future>
#include <thread>
/*
std::launch::async：马上开始
std::launch::defferd：在要值的时候才开始
*/

bool bufferdFileLoader()
{
    size_t bytesLoaded=0;
    while(bytesLoaded < 20000) {
        std::cout << "thread: loading file ..."<<std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
        bytesLoaded+=1000;
    }
    return true;
}


int std_async_complex_1_test()
{
    std::future<bool> bgThread= std::async(std::launch::async,bufferdFileLoader);

    std::future_status status;

    //Our main program loop
    while(true){
        std::cout<< "Main thread is running" << std::endl;
        //artificial sleep
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        status = bgThread.wait_for(std::chrono::milliseconds(1));

        //if oour data is ready, that is , our background thread has completed
        if(status == std::future_status::ready)
        {
            std::cout<<"our data is ready ..." <<std::endl;
            break;
        }

    }

    return 0;
}