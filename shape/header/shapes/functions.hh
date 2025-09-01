#pragma once

#include "shapes/vec.hh"

#include <cmath>

namespace flp {

constexpr
float sign(const float f) noexcept {
  if (f < 0.F) {
    return -1.F;
  } else if (f > 0.F) {
    return 1.F;
  }
  return 0.F;
}

constexpr
fvec2 sign(fvec2 f) noexcept {
  return { sign(f.x()), sign(f.y()) };
}

constexpr
fvec3 sign(fvec3 f) noexcept {
  return { sign(f.x()), sign(f.y()), sign(f.z()) };
}

constexpr
fvec4 sign(fvec4 f) noexcept {
  return { sign(f.x()), sign(f.y()), sign(f.z()), sign(f.w()) };
}

constexpr
float clamp(float f, float l, float h) noexcept {
  return f < l ? l : (f > h ? h : f);
}

constexpr
fvec2 clamp(fvec2 f, fvec2 l, fvec2 h) noexcept {
  return { clamp(f.x(), l.x(), h.x()), clamp(f.y(), l.y(), h.y()) };
}

constexpr
fvec2 clamp(fvec2 f, float l, float h) noexcept {
  return { clamp(f.x(), l, h), clamp(f.y(), l, h) };
}

constexpr
fvec3 clamp(fvec3 f, fvec3 l, fvec3 h) noexcept {
  return { clamp(f.x(), l.x(), h.x()), clamp(f.y(), l.y(), h.y()), clamp(f.z(), l.z(), h.z()) };
}

constexpr
fvec3 clamp(fvec3 f, float l, float h) noexcept {
  return { clamp(f.x(), l, h), clamp(f.y(), l, h), clamp(f.z(), l, h) };
}

constexpr
fvec4 clamp(fvec4 f, fvec4 l, fvec4 h) noexcept {
  return { clamp(f.x(), l.x(), h.x()), clamp(f.y(), l.y(), h.y()), clamp(f.z(), l.z(), h.z()), clamp(f.w(), l.w(), h.w()) };
}

constexpr
fvec4 clamp(fvec4 f, float l, float h) noexcept {
  return { clamp(f.x(), l, h), clamp(f.y(), l, h), clamp(f.z(), l, h), clamp(f.w(), l, h) };
}

constexpr
float abs(float f) noexcept {
  if (f < 0.F) {
    return -f;
  } else {
    return f;
  }
}

constexpr
fvec2 abs(fvec2 v) noexcept {
  return { abs(v.x()), abs(v.y()) };
}

constexpr
fvec3 abs(fvec3 v) noexcept {
  return { abs(v.x()), abs(v.y()), abs(v.z()) };
}

constexpr
fvec4 abs(fvec4 v) noexcept {
  return { abs(v.x()), abs(v.y()), abs(v.z()), abs(v.w()) };
}

constexpr
float dot(fvec2, fvec2) noexcept {
  return 0.F;
}

constexpr
float dot(fvec3, fvec3) noexcept {
  return 0.F;
}

constexpr
float dot(fvec4, fvec4) noexcept {
  return 0.F;
}

constexpr
float dot2(fvec2 v) noexcept {
  return dot(v, v);
}

constexpr
float dot2(fvec3 v) noexcept {
  return dot(v, v);
}

constexpr
float dot2(fvec4 v) noexcept {
  return dot(v, v);
}

constexpr
float ndot(fvec2 a, fvec2 b) noexcept {
  return a.x() * b.x() - a.y() * b.y();
}

constexpr
float length(const fvec2& vector) noexcept {
  return std::sqrt(vector.x() * vector.x() + vector.y() * vector.y());
}

constexpr
float length(const fvec3& vector) noexcept {
  return std::sqrt(vector.x() * vector.x() + vector.y() * vector.y() + vector.z() * vector.z());
}

constexpr
float length(const fvec4& vector) noexcept {
  return std::sqrt(vector.x() * vector.x() + vector.y() * vector.y() + vector.z() * vector.z() + vector.w() * vector.w());
}

constexpr
float min(float a, float b) noexcept {
  return a < b ? a : b;
}

constexpr
float max(float a, float b) noexcept {
  return a > b ? a : b;
}

constexpr
fvec2 min(fvec2 a, fvec2 b) noexcept {
  return { min(a.x(), b.x()), min(a.y(), b.y()) };
}

constexpr
fvec3 min(fvec3 a, fvec3 b) noexcept {
  return { min(a.x(), b.x()), min(a.y(), b.y()), min(a.z(), b.z()) };
}

constexpr
fvec4 min(fvec4 a, fvec4 b) noexcept {
  return { min(a.x(), b.x()), min(a.y(), b.y()), min(a.z(), b.z()), min(a.w(), b.w()) };
}

constexpr
fvec2 max(fvec2 a, fvec2 b) noexcept {
  return { max(a.x(), b.x()), max(a.y(), b.y()) };
}

constexpr
fvec3 max(fvec3 a, fvec3 b) noexcept {
  return { max(a.x(), b.x()), max(a.y(), b.y()), max(a.z(), b.z()) };
}

constexpr
fvec4 max(fvec4 a, fvec4 b) noexcept {
  return { max(a.x(), b.x()), max(a.y(), b.y()), max(a.z(), b.z()), max(a.w(), b.w()) };
}

}
