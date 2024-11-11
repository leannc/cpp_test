//
// Created by kang on 2024/11/11.
//

#include "Decorators.h"
#include "../ConferenceTicket.h"

void value_based_run_time_decorator() {
    Item item(Taxed(0.19,Discounted(0.2,ConferenceTicket{"kang",100.0})));
    std::cout<<"in value based runtime decorator,the item price is " << item.price()<<std::endl;
}