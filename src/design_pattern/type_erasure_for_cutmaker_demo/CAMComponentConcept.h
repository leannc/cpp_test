//
// Created by kang on 2024/11/9.
//

#pragma once

#include "../UseCase.h"
namespace type_erasure {

class CAMComponentConcept {
 public:
    virtual ~CAMComponentConcept() = default;

    virtual void update() = 0;
    virtual std::unique_ptr<CAMComponentConcept> clone() const = 0;
};

}  // namespace type_erasure


