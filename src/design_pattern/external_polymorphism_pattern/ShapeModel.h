//
// Created by kang on 2024/11/9.
//

#ifndef CPP_TEST_SHAPEMODEL_H
#define CPP_TEST_SHAPEMODEL_H

#include "ShapeConcept.h"

template<typename ShapeT>
double perimeter(ShapeT);


template<typename ShapeT>
class ShapeModel : public ShapeConcept {
public:
    using DrawStrategy = std::function<void(ShapeT const&)>;

     ShapeModel(ShapeT shape_, DrawStrategy drawer_)
    : shape(std::move(shape_))
    , drawer(std::move(drawer_))
    {}

    void draw() const override { drawer(shape);}
    double area() const override { return shape.area();}
    double perimeter() const override {return perimeter<ShapeT>(shape);}
    double origin(std::function<double(void)>  getOrigin) const override {return getOrigin();}

private:
    ShapeT shape;
    DrawStrategy drawer;
};


#endif //CPP_TEST_SHAPEMODEL_H
