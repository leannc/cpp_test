//
// Created by kang on 2024/11/9.
//

#ifndef CPP_TEST_SHAPEMODEL_H
#define CPP_TEST_SHAPEMODEL_H

#include "ShapeConcept.h"

namespace type_erasure {

template<typename ShapeT>
double perimeter(ShapeT);


template<typename ShapeT,typename DrawStrategy>
class OwningShapeModel : public ShapeConcept {
public:
    OwningShapeModel(ShapeT shape_, DrawStrategy drawer_)
        : shape(std::move(shape_)), drawer(std::move(drawer_)) {}

    void draw() const override { drawer(shape); }
    std::unique_ptr<ShapeConcept> clone() const override {
        return std::make_unique<OwningShapeModel>(*this);
    }


private:
    ShapeT shape;
    DrawStrategy drawer;
};

}
#endif //CPP_TEST_SHAPEMODEL_H