/**
 *  \author  Olivia Quinet
 */

#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <te2/default_visitor.hpp>
#include <te2/te2.hpp>

namespace Hera {

struct Visitor;

struct DocumentEntityVtbl {
  void (*traverse)(void*, size_t&);
  void (*accept_visitor)(const void*, const Visitor&);

  template <typename CastT>
  static DocumentEntityVtbl create() {
    return {
        .traverse = [](void* p, size_t& sum) { return CastT::value(p).traverse(sum); },
        .accept_visitor = [](const void* p, const Visitor& visitor) { return visitor(CastT::value(p)); },
    };
  }
};

using VISITOR_STRATEGY = te2::visitor::default_visitor_strategy;
using BASE = te2::base<DocumentEntityVtbl, VISITOR_STRATEGY>;

struct DocumentEntity : public BASE {
  template <typename DocumentEntityT>
  DocumentEntity(DocumentEntityT&& entity) : BASE(std::forward<DocumentEntityT>(entity)) {}

  auto traverse(size_t& sum) { return vtbl().traverse(pimpl(), sum); }
};

}  // namespace Hera

#endif
