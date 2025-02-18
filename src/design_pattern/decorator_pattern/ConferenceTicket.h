//
// Created by kang on 2024/11/11.
//

#pragma once

#include "../UseCase.h"

class ConferenceTicket {
 public:
    ConferenceTicket(std::string name, double price):name_(std::move(name)), price_(price) {}

    std::string const& name() const {return name_;}
    double price() const {return price_;}

 private:
    std::string name_;
    double price_;
};
