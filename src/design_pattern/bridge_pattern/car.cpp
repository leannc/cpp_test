//
// Created by kang on 2024/11/7.
//

#include "car.h"

struct Car::Engine {
    double speed;
    std::string band;
    std::string alarm;
};


Car::Car() : engine(std::make_unique<Engine>())
{
    engine->speed = 10;
    engine->band="BYD";
    engine->alarm="diiiii";
}

Car::~Car() = default;

double Car::speed() {
    return engine->speed;
}

std::string Car::engineBand() {
    return engine->band;
}

void Car::alarm() {
    std::cout<<engine->alarm<<std::endl;
}

