#pragma once

#include "core/span.hh"

#include <array>

namespace flp {

template<typename Type, Type ...Values>
struct Extents {
  static constexpr auto rank = sizeof...(Values);

  std::array extent_arr{ Values... };
};

template<typename Type, typename Extents>
struct MDSpan {
  template<typename OtherExtentType, size_t OtherRank>
  MDSpan(Type*, Span<OtherExtentType, OtherRank> exts);
};

}
