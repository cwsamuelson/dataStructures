#pragma once

#include <array>
#include <cstddef>
#include <stdexcept>

namespace flp {

template<typename Type, size_t Count>
struct vecn;

template<typename Vec, typename Type, size_t... Indices>
struct Swizzle {
  template<typename OVec, typename OType, size_t... OIndices>
  constexpr Swizzle& operator=(const Swizzle<OVec, OType, OIndices...>& other) {
    ((vec[Indices] = other.vec[OIndices]), ...);
    return *this;
  }

  constexpr Swizzle& operator=(const std::array<Type, sizeof...(Indices)>& array) {
    [this]<size_t... I>(const auto& array, std::integer_sequence<size_t, I...>) {
      ((vec.values[Indices] = array[I]), ...);
    }(array, std::make_integer_sequence<size_t, sizeof...(Indices)>());

    return *this;
  }

  constexpr Swizzle& operator=(const vecn<Type, sizeof...(Indices)>& other) noexcept {
    ((vec.values[Indices] = other.values[Indices]), ...);
    return *this;
  }

  // template<size_t ...OIndices>
  // constexpr
  // operator Swizzle<OVec, OType, OIndices...>() {
  //   return Swizzle<Vec, Type, OIndices...>(vec[Indices]...);
  // }

  constexpr operator std::array<Type, sizeof...(Indices)>() const noexcept {
    return { vec[Indices]... };
  }

  constexpr operator vecn<Type, sizeof...(Indices)>() const noexcept {
    return vecn<Type, sizeof...(Indices)>(vec.values[Indices]...);
  }

  friend constexpr vecn<Type, sizeof...(Indices)> operator*(const float scalar, const Swizzle& swizzle) noexcept {
    const vecn<Type, sizeof...(Indices)> vec(swizzle);
    return scalar * vec;
  }

  Vec& vec;
};

constexpr size_t get_swiz_index(const char c) {
  switch (c) {
  case 'x':
  case 'r':
  case 's':
    return 0;
  case 'y':
  case 'g':
  case 't':
    return 1;
  case 'z':
  case 'b':
  case 'p':
    return 2;
  case 'w':
  case 'a':
  case 'q':
    return 3;
  case '\0':
    return 0;
  default:
    throw std::runtime_error("Invalid character in swizzle expression");
  }
}

template<size_t N>
struct SwizTag {
  char data[N] {};

  consteval SwizTag(const char (&str)[N]) noexcept {
    for (size_t i = 0; i < N; ++i) {
      data[i] = str[i];
    }
  }
};

template<SwizTag Tag>
struct SwizTagType {};

template<SwizTag Tag>
consteval auto operator""_swz() noexcept {
  return SwizTagType<Tag> {};
}

template<SwizTag Tag>
consteval auto get_swiz_indices(SwizTagType<Tag>) {
  return []<size_t... Indices>(std::index_sequence<Indices...>) {
    return std::integer_sequence<size_t, get_swiz_index(Tag.data[Indices])...> {};
  }(std::make_index_sequence<sizeof(Tag.data) - 1>());
}

template<char... Chars>
using SwizIndexSequence = std::integer_sequence<size_t, get_swiz_index(Chars)...>;

} // namespace flp
