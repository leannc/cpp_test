//
// Created by kang on 2024/11/9.
//

#pragma once

#include "CAMComponentConcept.h"

namespace type_erasure {

// template<typename ShapeT>
// double perimeter(ShapeT);


template<typename CAM_T, typename UpdateFunction>
class OwningCAMComponentModel : public CAMComponentConcept {
 public:
    OwningCAMComponentModel(CAM_T comp, UpdateFunction updater)
        : comp_(std::move(comp)), updater_(std::move(updater)) {}

    void update() override { updater_(comp_); }
    std::unique_ptr<CAMComponentConcept> clone() const override {
        return std::make_unique<OwningCAMComponentModel>(*this);
    }

 private:
    CAM_T comp_;
    UpdateFunction updater_;
};
}  // namespace type_erasure


