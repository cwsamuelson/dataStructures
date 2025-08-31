#pragma once

#include "shapes/swizzling.hh"

namespace flp {

struct vec4 {
  constexpr
  vec4() noexcept
    : vec4(0.F)
  {}

  constexpr
  vec4(const float value) noexcept
    : vec4(value, value, value, value)
  {}

  constexpr
  vec4(const float a, const float b, const float c, const float d) noexcept
    : x(a)
    , y(b)
    , z(c)
    , w(d)
  {}

  constexpr
  vec4(const vec2& vec1, const vec2& vec2) noexcept
    : x(vec1.x)
    , y(vec1.y)
    , z(vec2.x)
    , w(vec2.y)
  {}

  constexpr
  vec4(const vec2& vec, const float value1, const float value2) noexcept
    : x(vec.x)
    , y(vec.y)
    , z(value1)
    , w(value2)
  {}

  constexpr
  vec4(const float value1, const vec2& vec, const float value2) noexcept
    : x(value1)
    , y(vec.x)
    , z(vec.y)
    , w(value2)
  {}

  constexpr
  vec4(const float value1, const float value2, const vec2& vec) noexcept
    : x(value1)
    , y(value2)
    , z(vec.x)
    , w(vec.y)
  {}

  constexpr
  vec4(const vec3& vec, const float value) noexcept
    : x(vec.x)
    , y(vec.y)
    , z(vec.z)
    , w(value)
  {}

  constexpr
  vec4(const float value, const vec3& vec) noexcept
    : x(value)
    , y(vec.x)
    , z(vec.y)
    , w(vec.z)
  {}

  float x{};
  float y{};
  float z{};
  float w{};

  friend auto operator<=>(const vec4&, const vec4&) noexcept = default;

  Swiz4All
};

constexpr
vec4 operator+(const vec4& lhs, const vec4& rhs) noexcept {
  return { lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w };
}

constexpr
vec4 operator-(const vec4& lhs, const vec4& rhs) noexcept {
  return { lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w };
}

constexpr
vec4 operator*(const float scale, const vec4& vec) noexcept {
  return { vec.x * scale, vec.y * scale, vec.z * scale, vec.w * scale };
}

constexpr
vec4 operator*(const vec4& vec, const float scale) noexcept {
  return { vec.x * scale, vec.y * scale, vec.z * scale, vec.w * scale };
}

constexpr
vec4 operator/(const float scale, const vec4& vec) noexcept {
  return { vec.x / scale, vec.y / scale, vec.z / scale, vec.w / scale };
}

constexpr
vec4 operator/(const vec4& vec, const float scale) noexcept {
  return { vec.x / scale, vec.y / scale, vec.z / scale, vec.w / scale };
}

}
