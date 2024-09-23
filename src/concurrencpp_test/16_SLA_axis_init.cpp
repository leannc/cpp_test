//
// Created by kang on 2024/7/28.
//

#include "concurrencpp/concurrencpp.h"

#include <iostream>
#include <ctime>

using namespace concurrencpp;

using namespace std::chrono_literals;

//方便起见的全局变量
int i=0;
async_lock _lock;
//----------------方便起见的全局变量


std::string currentTime() {
    time_t now = time(0);

    // 将秒数转换为本地时间结构
    tm* localTime = localtime(&now);

    // 格式化时间为字符串
    char timeStr[100];
    strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S ", localTime);

    std::string time = timeStr;
    return time;
}

//模拟立即返回的状态查询函数
concurrencpp::generator<bool> is_moving() {

    while (true) {
        if(i>10)
        {
            i=0;
            co_yield false;
        }
        co_yield true;
    }

}

result<int> axis_move_task(std::shared_ptr<concurrencpp::thread_pool_executor> tpe,std::shared_ptr<concurrencpp::timer_queue> tq,result<int>&& preivous_task,int distance,std::string axis_name)
{
    auto result = co_await preivous_task;
    if (result == -1)
    {
        auto guard = co_await _lock.lock(tpe);
        std::cout <<"<task begin> : "<< axis_name << " move " <<std::this_thread::get_id()<<std::endl;
    } else
    {
        auto guard = co_await _lock.lock(tpe);
        std::cout<< currentTime()  << axis_name << ": previous task done!  begin to move task " <<std::this_thread::get_id()<<std::endl;
    }


    //触发运动接口

    //查询运动是否结束
    for (auto moving : is_moving())
    {
        if (false == moving)
        {
            auto guard = co_await _lock.lock(tpe);
            std::cout << currentTime() << axis_name <<" moving done!"<<std::endl;
            break;
        } else
        {
            auto guard = co_await _lock.lock(tpe);
            std::cout << currentTime() << axis_name <<" is still moving"<<std::endl;
        }
        //等一段时间再查询
        co_await tq->make_delay_object(1500ms, tpe);
    }
    co_return 0;
}



result<int> axis_go_origin_task(std::shared_ptr<concurrencpp::thread_pool_executor> tpe,std::shared_ptr<concurrencpp::timer_queue> tq,result<int>&& preivous_task,std::string axis_name)
{
    auto result = co_await preivous_task;
    if (result == -1)
    {

        std::cout <<"<task begin> "<< axis_name << " go origin " <<std::this_thread::get_id()<<std::endl;
    } else
    {
        auto guard = co_await _lock.lock(tpe);
        std::cout<< currentTime()  << axis_name << ": previous task done!  begin to move task " <<std::this_thread::get_id()<<std::endl;
    }

    {
        auto guard = co_await _lock.lock(tpe);
        std::cout << currentTime() << axis_name << " starts to go origin " <<std::this_thread::get_id()<<std::endl;
    }


    //调用运动接口，往原点的方向走

    //查询运动是否结束
    for (auto moving : is_moving())
    {
        if (false == moving)
        {
            auto guard = co_await _lock.lock(tpe);
            std::cout << currentTime() << axis_name <<" arrived at origin !"<<std::endl;
            break;
        } else
        {
            auto guard = co_await _lock.lock(tpe);
            std::cout << currentTime() << axis_name <<" is still origining"<<std::endl;
        }
        //等一段时间再查询
        co_await tq->make_delay_object(1500ms, tpe);
    }

    {
        auto guard = co_await _lock.lock(tpe);
        //坐标设置为0；
        std::cout<< currentTime()  << axis_name << "'s coordinate is set to 0"<<std::endl;

        //回原偏移
        std::cout << currentTime() << axis_name << " begin to offset a distance"<<std::endl;
    }


    //回原偏移完成
    for (auto moving_finish : is_moving())
    {
        if (moving_finish)
        {
            auto guard = co_await _lock.lock(tpe);
            std::cout << currentTime() << axis_name <<" offset distance done !"<<std::endl;
            break;
        } else
        {
            auto guard = co_await _lock.lock(tpe);
            std::cout << currentTime() << axis_name <<" is still offsetting"<<std::endl;
        }
        //等一段时间再查询
        co_await tq->make_delay_object(1500ms, tpe);
    }

    auto guard = co_await _lock.lock(tpe);
    std::cout<< currentTime()  << axis_name << " finished to go origin " <<std::this_thread::get_id()<<std::endl;
    co_return 0;
}

result<int> start_task()
{
    co_return -1;
}


int SLA_axis_init()
{
    runtime runtime;
    const auto thread_pool_executor = runtime.thread_pool_executor();

    concurrencpp::timer timer = runtime.timer_queue()->make_timer(3s, 3s, thread_pool_executor, [&] {
        i=100;
    });

     runtime.timer_queue()->make_delay_object(0ms,thread_pool_executor);

     auto recoater_platform_init_task = start_task();
     auto resin_init_task=start_task();


    //刮刀轴回零
    recoater_platform_init_task = axis_go_origin_task(thread_pool_executor,runtime.timer_queue(),std::move(recoater_platform_init_task),"recoater");
    //网板回零
    recoater_platform_init_task = axis_go_origin_task(thread_pool_executor,runtime.timer_queue(),std::move(recoater_platform_init_task),"platform");
    //网板运动到指定位置
    recoater_platform_init_task = axis_move_task(thread_pool_executor,runtime.timer_queue(),std::move(recoater_platform_init_task),10,"platform");


    //液位轴回零
    resin_init_task = axis_go_origin_task(thread_pool_executor,runtime.timer_queue(),std::move(resin_init_task),"resin");
    //液位轴运动到指定位置
    resin_init_task = axis_move_task(thread_pool_executor,runtime.timer_queue(),std::move(resin_init_task),10,"resin");


    recoater_platform_init_task.get();
    resin_init_task.get();

    return 0;
}