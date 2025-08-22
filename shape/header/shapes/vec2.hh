#pragma once

#include "shapes/swizzling.hh"

#include <type_traits>

namespace flp {

struct vec2 {
  constexpr
  vec2() noexcept
    : vec2(0.F)
  {}

  constexpr
  vec2(const float value) noexcept
    : vec2(value, value)
  {}

  constexpr
  vec2(const float a, const float b) noexcept
    : x(a)
    , y(b)
  {}

  float x{};
  float y{};

  friend auto operator<=>(const vec2&, const vec2&) noexcept = default;

  Swiz2All
};

constexpr
vec2 operator+(const vec2& lhs, const vec2& rhs) noexcept {
  return { lhs.x + rhs.x, lhs.y + rhs.y };
}

constexpr
vec2 operator-(const vec2& lhs, const vec2& rhs) noexcept {
  return { lhs.x - rhs.x, lhs.y - rhs.y };
}

constexpr
vec2 operator*(const vec2& vec, const float scale) noexcept {
  return { vec.x * scale, vec.y * scale };
}

constexpr
vec2 operator*(const float scale, const vec2& vec) noexcept {
  return { vec.x * scale, vec.y * scale };
}

}
