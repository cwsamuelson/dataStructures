#pragma once

#include <array>
#include <cstddef>

namespace flp {

template<typename Type, size_t Count>
struct vecn;

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
    return { vec[Indices]... };
  }

  constexpr
  Swizzle& operator=(const std::array<Type, sizeof...(Indices)>& array) {
    [this]<size_t ...I>(const auto& array, std::integer_sequence<size_t, I...>) {
      ((vec.values[Indices] = array[I]), ...);
    } (array, std::make_integer_sequence<size_t, sizeof...(Indices)>());

    return *this;
  }

  constexpr
  Swizzle& operator=(const vecn<Type, sizeof...(Indices)>& other) noexcept {
    ((vec.values[Indices] = other.values[Indices]), ...);
    return *this;
  }

  Vec& vec;
};

template<char...Cs>
struct SwizTag {};

template<typename Type, Type ...Chars>
constexpr
SwizTag<Chars...> operator""_swz() noexcept {
  return {};
}

constexpr
size_t get_swiz_index(const char c) {
  switch (c) {
    case 'x':
    case 'r':
      return 0;
    case 'y':
    case 'g':
      return 1;
    case 'z':
    case 'b':
      return 2;
    case 'w':
    case 'a':
      return 3;
    default:
      throw std::runtime_error("Invalid character in swizzle expression");
  }
}

template<char...Chars>
using SwizIndexSequence = std::integer_sequence<size_t, get_swiz_index(Chars)...>;

}
