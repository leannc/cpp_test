//
// Created by kang on 2024/11/9.
//

#ifndef CPP_TEST_SHAPECONCEPT_H
#define CPP_TEST_SHAPECONCEPT_H

#include "../UseCase.h"

class ShapeConcept {
public:
    virtual ~ShapeConcept() = default;
    virtual void draw() const = 0 ;
    virtual double origin(std::function<double(void)> = [](){return 7.8;}) const  = 0;
    virtual double area() const = 0;
    virtual double perimeter() const =0;
};




#endif //CPP_TEST_SHAPECONCEPT_H
