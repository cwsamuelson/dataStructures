#pragma once

#include "shapes/swizzling.hh"

namespace flp {

struct vec3 {
  constexpr
  vec3() noexcept
    : vec3(0.F)
  {}

  constexpr
  vec3(const float value) noexcept
    : vec3(value, value, value)
  {}

  constexpr
  vec3(const float a, const float b, const float c) noexcept
    : x(a)
    , y(b)
    , z(c)
  {}

  constexpr
  vec3(const vec2& vec, const float f)
    : x(vec.x)
    , y(vec.y)
    , z(f)
  {}

  constexpr
  vec3(const float f, const vec2& vec)
    : x(f)
    , y(vec.x)
    , z(vec.y)
  {}

  float x{};
  float y{};
  float z{};

  friend auto operator<=>(const vec3&, const vec3&) noexcept = default;

  Swiz3All
};

constexpr
vec3 operator+(const vec3& lhs, const vec3& rhs) noexcept {
  return { lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z };
}

constexpr
vec3 operator-(const vec3& lhs, const vec3& rhs) noexcept {
  return { lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z };
}

constexpr
vec3 operator*(const float scale, const vec3& vec) noexcept {
  return { vec.x * scale, vec.y * scale, vec.z * scale };
}

constexpr
vec3 operator*(const vec3& vec, const float scale) noexcept {
  return { vec.x * scale, vec.y * scale, vec.z * scale };
}

constexpr
vec3 operator/(const float scale, const vec3& vec) noexcept {
  return { vec.x / scale, vec.y / scale, vec.z / scale };
}

constexpr
vec3 operator/(const vec3& vec, const float scale) noexcept {
  return { vec.x / scale, vec.y / scale, vec.z / scale };
}

}
