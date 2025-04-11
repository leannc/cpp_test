/**
 *  \author  Olivia Quinet
 */

#ifndef ANIMAL2_VISITOR_HPP
#define ANIMAL2_VISITOR_HPP

#include "DocumentEntity.h"

#include "BM_Contours.h"

#include <functional>

namespace Hera {

template <typename _Tp>
using VISITOR_FCT = std::function<void(_Tp _x)>;
struct Visitor : public VISITOR_STRATEGY::visitor<Visitor, VISITOR_FCT, const CAMContour&> {};
// struct Visitor : public VISITOR_STRATEGY::visitor<Visitor, VISITOR_FCT, const Sheep&, const Cow&> {};

}  // namespace Hera
#endif
