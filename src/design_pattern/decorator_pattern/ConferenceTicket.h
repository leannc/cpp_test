//
// Created by kang on 2024/11/11.
//

#ifndef CPP_TEST_CONFERENCETICKET_H
#define CPP_TEST_CONFERENCETICKET_H

#include "../UseCase.h"

class ConferenceTicket
{
public:
    ConferenceTicket(std::string name,double price):name_(std::move(name)),price_(price){}

    std::string const& name() const {return name_;}
    double price() const {return price_;}

private:
    std::string name_;
    double price_;
};



#endif //CPP_TEST_CONFERENCETICKET_H
