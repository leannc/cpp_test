//
// Created by kang on 2024/11/11.
//
#include "../ConferenceTicket.h"
#include "Decorators.h"


void compile_time_decorator()
{
    Taxed<0.15,Discounted<0.1,ConferenceTicket>> item{"",100.0};
    std::cout<<"the item price is "<<item.price()<<std::endl;
}
