#pragma once

#include "shapes/vec.hh"

#include <algorithm>
#include <cmath>

namespace flp {

constexpr float sign(const float f) noexcept {
  if (f < 0.F) {
    return -1.F;
  } else if (f > 0.F) {
    return 1.F;
  }
  return 0.F;
}

constexpr fvec2 sign(const fvec2 f) noexcept {
  return { sign(f.x()), sign(f.y()) };
}

constexpr fvec3 sign(const fvec3 f) noexcept {
  return { sign(f.x()), sign(f.y()), sign(f.z()) };
}

constexpr fvec4 sign(const fvec4 f) noexcept {
  return { sign(f.x()), sign(f.y()), sign(f.z()), sign(f.w()) };
}

constexpr float clamp(const float f, const float l, const float h) noexcept {
  return f < l ? l : (f > h ? h : f);
}

constexpr fvec2 clamp(const fvec2 f, const fvec2 l, const fvec2 h) noexcept {
  return { clamp(f.x(), l.x(), h.x()), clamp(f.y(), l.y(), h.y()) };
}

constexpr fvec2 clamp(const fvec2 f, const float l, const float h) noexcept {
  return { clamp(f.x(), l, h), clamp(f.y(), l, h) };
}

constexpr fvec3 clamp(const fvec3 f, const fvec3 l, const fvec3 h) noexcept {
  return { clamp(f.x(), l.x(), h.x()), clamp(f.y(), l.y(), h.y()), clamp(f.z(), l.z(), h.z()) };
}

constexpr fvec3 clamp(const fvec3 f, const float l, const float h) noexcept {
  return { clamp(f.x(), l, h), clamp(f.y(), l, h), clamp(f.z(), l, h) };
}

constexpr fvec4 clamp(const fvec4 f, const fvec4 l, const fvec4 h) noexcept {
  return {
    clamp(f.x(), l.x(), h.x()), clamp(f.y(), l.y(), h.y()), clamp(f.z(), l.z(), h.z()), clamp(f.w(), l.w(), h.w())
  };
}

constexpr fvec4 clamp(const fvec4 f, const float l, const float h) noexcept {
  return { clamp(f.x(), l, h), clamp(f.y(), l, h), clamp(f.z(), l, h), clamp(f.w(), l, h) };
}

constexpr float abs(const float f) noexcept {
  if (f < 0.F) {
    return -f;
  } else {
    return f;
  }
}

constexpr fvec2 abs(const fvec2 v) noexcept {
  return { abs(v.x()), abs(v.y()) };
}

constexpr fvec3 abs(const fvec3 v) noexcept {
  return { abs(v.x()), abs(v.y()), abs(v.z()) };
}

constexpr fvec4 abs(const fvec4 v) noexcept {
  return { abs(v.x()), abs(v.y()), abs(v.z()), abs(v.w()) };
}

//!@TODO implement `dot`
constexpr float dot(const fvec2, const fvec2) noexcept {
  return 0.F;
}

constexpr float dot(const fvec3, const fvec3) noexcept {
  return 0.F;
}

constexpr float dot(const fvec4, const fvec4) noexcept {
  return 0.F;
}

constexpr float dot2(const fvec2 v) noexcept {
  return dot(v, v);
}

constexpr float dot2(const fvec3 v) noexcept {
  return dot(v, v);
}

constexpr float dot2(const fvec4 v) noexcept {
  return dot(v, v);
}

constexpr float ndot(const fvec2 a, const fvec2 b) noexcept {
  return a.x() * b.x() - a.y() * b.y();
}

constexpr float sqrt(const float n) {
  if (std::is_constant_evaluated()) {
    if (n < 0.F) return 0.F;
    if (n == 0.F) return 0.F;
    float x = n;
    float y = (x + 1) / 2;
    while (abs(y - x) > 0.0001F) {
      x = y;
      y = (x + n / x) / 2;
    }
    return x;
  } else {
    return std::sqrt(n);
  }
}

constexpr
float length(const fvec2& vector) noexcept {
  return flp::sqrt((vector.x() * vector.x()) + (vector.y() * vector.y()));
}

constexpr
float length(const fvec3& vector) noexcept {
  return flp::sqrt((vector.x() * vector.x()) + (vector.y() * vector.y()) + (vector.z() * vector.z()));
}

constexpr
float length(const fvec4& vector) noexcept {
  return flp::sqrt((vector.x() * vector.x()) + (vector.y() * vector.y()) + (vector.z() * vector.z())
                   + (vector.w() * vector.w()));
}

constexpr float min(const float a, const float b) noexcept {
  return a < b ? a : b;
}

constexpr float max(const float a, const float b) noexcept {
  return a > b ? a : b;
}

constexpr fvec2 min(const fvec2 a, const fvec2 b) noexcept {
  return { min(a.x(), b.x()), min(a.y(), b.y()) };
}

constexpr fvec3 min(const fvec3 a, const fvec3 b) noexcept {
  return { min(a.x(), b.x()), min(a.y(), b.y()), min(a.z(), b.z()) };
}

constexpr fvec4 min(const fvec4 a, const fvec4 b) noexcept {
  return { min(a.x(), b.x()), min(a.y(), b.y()), min(a.z(), b.z()), min(a.w(), b.w()) };
}

constexpr fvec2 max(const fvec2 a, const fvec2 b) noexcept {
  return { max(a.x(), b.x()), max(a.y(), b.y()) };
}

constexpr fvec3 max(const fvec3 a, const fvec3 b) noexcept {
  return { max(a.x(), b.x()), max(a.y(), b.y()), max(a.z(), b.z()) };
}

constexpr fvec4 max(const fvec4 a, const fvec4 b) noexcept {
  return { max(a.x(), b.x()), max(a.y(), b.y()), max(a.z(), b.z()), max(a.w(), b.w()) };
}

constexpr
float pow(const float a, const float b) noexcept {
  if (std::is_constant_evaluated()) {
    return 0.F; //!@TODO implement `constexpr pow`
  } else {
    return std::pow(a, b);
  }
}

constexpr fvec2 pow(const fvec2 a, const fvec2 b) noexcept {
  return { pow(a.x(), b.x()), pow(a.y(), b.y()) };
}

constexpr fvec3 pow(const fvec3 a, const fvec3 b) noexcept {
  return { pow(a.x(), b.x()), pow(a.y(), b.y()), pow(a.z(), b.z()) };
}

constexpr fvec4 pow(const fvec4 a, const fvec4 b) noexcept {
  return { pow(a.x(), b.x()), pow(a.y(), b.y()), pow(a.z(), b.z()), pow(a.w(), b.w()) };
}

constexpr float fmod(const float a, const float b) noexcept {
  if (std::is_constant_evaluated()) {
    return a - static_cast<int>(a / b) * b;
  } else {
    return std::fmod(a, b);
  }
}

constexpr bool all(const bvec2& vec) noexcept {
  return std::ranges::all_of(vec.values, std::identity {});
}

constexpr bool all(const bvec3& vec) noexcept {
  return std::ranges::all_of(vec.values, std::identity {});
}

constexpr bool all(const bvec4& vec) noexcept {
  return std::ranges::all_of(vec.values, std::identity {});
}

constexpr bvec2 negate(const bvec2& vec) noexcept {
  return { not vec.values[0], not vec.values[1] };
}

constexpr bvec3 negate(const bvec3& vec) noexcept {
  return { not vec.values[0], not vec.values[1], not vec.values[2] };
}

constexpr bvec4 negate(const bvec4& vec) noexcept {
  return { not vec.values[0], not vec.values[1], not vec.values[2], not vec.values[3] };
}

} // namespace flp
