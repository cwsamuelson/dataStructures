#pragma once

#include <array>
#include <cstddef>

namespace flp {

template<typename Vec, typename Type, size_t ...Indices>
struct Swizzle {
  template<typename OVec, typename OType, size_t ...OIndices>
  constexpr
  Swizzle& operator=(const Swizzle<OVec, OType, OIndices...>& other) {
    ((vec[Indices] = other.vec[OIndices]), ...);
    return *this;
  }

  constexpr
  operator std::array<Type, sizeof...(Indices)>() const noexcept {
    return { vec.at(Indices)... };
  }

  Vec& vec;
};

template<char...Cs>
struct SwizTag {};

template<char...Cs>
constexpr
SwizTag<Cs...> operator""_swz() noexcept {
  return {};
}

}
