#pragma once

#include "algorithms/comparison.hh"

#include <optional>
#include <utility>

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

template<typename Type>
constexpr
auto abs(const Type& value) noexcept {
  if (value < 0) {
    return -value;
  }

  return value;
}

template<typename Type>
constexpr
auto gcd(Type value1, Type value2) noexcept {
  while (value2 != 0) {
    value1 = std::exchange(value2, value1 % value2);
  }

  return value1;
}

template<typename Type>
constexpr
auto lcm(Type value1, Type value2) noexcept {
  return abs(value1 * value2) / gcd(value1, value2);
}

}
