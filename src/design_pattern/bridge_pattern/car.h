//
// Created by kang on 2024/11/7.
//

#ifndef CPP_TEST_CAR_H
#define CPP_TEST_CAR_H

#include "../UseCase.h"

class Car{
public:
    explicit Car();
    ~Car();

    void alarm();
    double speed();
    std::string engineBand();

private:
    struct Engine;
    std::unique_ptr<Engine> engine;
};








#endif //CPP_TEST_CAR_H
