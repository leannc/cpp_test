//
// Created by kang on 2024/11/7.
//

#include "car.h"


void pimple_bridge_pattern() {
    Car mycar;
    std::cout<<"the band is : "<<mycar.engineBand()<<", speed is : "<<mycar.speed()<<std::endl;
}