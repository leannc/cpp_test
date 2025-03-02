//
// Created by kang on 2024/11/10.
//

#pragma once

#include "OwningCAMComponentModel.h"

class CAMComponent {
 public:
  template <typename CAM_T, typename UpdateFunc>
  CAMComponent(CAM_T comp, UpdateFunc update) {
    using Model = type_erasure::OwningCAMComponentModel<CAM_T, UpdateFunc>;
    pimpl = std::make_unique<Model>(std::move(comp), std::move(update));
  }

  CAMComponent(CAMComponent const &other) : pimpl(other.pimpl->clone()) {}

  CAMComponent &operator=(CAMComponent const &other) {
    CAMComponent copy(other);
    pimpl.swap(copy.pimpl);
    return *this;
  }

  ~CAMComponent() = default;
  CAMComponent(CAMComponent &&) = default;
  CAMComponent &operator=(CAMComponent &&) = default;

  void update() { pimpl->update(); }

 private:
  std::unique_ptr<type_erasure::CAMComponentConcept> pimpl;
  //    void draw() {pimpl->draw();}
};
