//
// Created by kang on 2024/11/10.
//

#pragma once

#include "OwningShapeModel.h"

class Shape {
 public:
    template<typename ShapeT, typename DrawStrategy>
    Shape(ShapeT shape, DrawStrategy drawer) {
        using Model = type_erasure::OwningShapeModel<ShapeT, DrawStrategy>;
        pimpl = std::make_unique<Model>(std::move(shape), std::move(drawer));
    }

    Shape(Shape const& other) : pimpl(other.pimpl->clone()) {}

    Shape& operator=(Shape const& other) {
        Shape copy(other);
        pimpl.swap(copy.pimpl);
        return *this;
    }

    ~Shape() = default;
    Shape(Shape&&) = default;
    Shape& operator=(Shape&&) = default;

    void draw() {
        pimpl->draw();
    }

 private:
    std::unique_ptr<type_erasure::ShapeConcept> pimpl;
//    void draw() {pimpl->draw();}
};



