//
// Created by kang on 2024/11/9.
//

#ifndef CPP_TEST_SHAPECONCEPT_H
#define CPP_TEST_SHAPECONCEPT_H

#include "../UseCase.h"
namespace type_erasure {

class ShapeConcept {
public:
    virtual ~ShapeConcept() = default;

    virtual void draw() const = 0;
    virtual std::unique_ptr<ShapeConcept> clone() const = 0;
};

}


#endif //CPP_TEST_SHAPECONCEPT_H
