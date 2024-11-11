//
// Created by kang on 2024/11/11.
//

#ifndef CPP_TEST_DECORATORS_H
#define CPP_TEST_DECORATORS_H

#include "Items.h"

class Discounted
{
public:
    Discounted(double discount, Item item)
    : item_(std::move(item))
    , factor_(discount)
    {}

    double price() const {return item_.price()*factor_;}

private:
    Item item_;
    double factor_;
};

class Taxed
{
public:
    Taxed(double taxRate,Item item)
    : item_(item)
    , taxRate_(taxRate)
    {}

    double price() const { return item_.price()*(1+taxRate_);}
private:
    Item item_;
    double taxRate_;
};



#endif //CPP_TEST_DECORATORS_H
