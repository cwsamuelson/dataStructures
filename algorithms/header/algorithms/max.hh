#pragma once

#include "algorithms/comparison.hh"

#include <optional>

namespace flp {

namespace {

template<typename Type, typename Compare>
constexpr
decltype(auto) impl(const Type& a, const Type& b, Compare compare) {
  return compare(a, b) ? a : b;
}

}

template<typename Type, typename Compare>
constexpr
decltype(auto) max(const Type& a, const Type& b, Compare compare) {
  return impl(a, b, compare);
}

template<typename Type, typename Compare>
constexpr
decltype(auto) min(const Type& a, const Type& b, Compare compare) {
  return impl(a, b, compare);
}

template<typename Type>
constexpr
decltype(auto) max(const Type& a, const Type& b) {
  return max(a, b, Greater{});
}

template<typename Type>
constexpr
decltype(auto) min(const Type& a, const Type& b) {
  return min(a, b, Less{});
}

} // namespace flp
