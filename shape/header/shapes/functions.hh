#pragma once

#include "shapes/common.hh"

namespace flp {

constexpr
float sign(float f) noexcept {
  if (f < 0.F) {
    return -1.F;
  } else if (f > 0.F) {
    return 1.F;
  }
  return 0.F;
}

constexpr
vec2 sign(vec2 f) noexcept {
  return { sign(f.x), sign(f.y) };
}

constexpr
vec3 sign(vec3 f) noexcept {
  return { sign(f.x), sign(f.y), sign(f.z) };
}

constexpr
float clamp(float f, float l, float h) noexcept {
  return f < l ? l : (f > h ? h : f);
}

constexpr
vec2 clamp(vec2 f, vec2 l, vec2 h) noexcept {
  return { clamp(f.x, l.x, h.x), clamp(f.y, l.y, h.y) };
}

constexpr
vec2 clamp(vec2 f, float l, float h) noexcept {
  return { clamp(f.x, l, h), clamp(f.y, l, h) };
}

constexpr
vec3 clamp(vec3 f, vec3 l, vec3 h) noexcept {
  return { clamp(f.x, l.x, h.x), clamp(f.y, l.y, h.y), clamp(f.z, l.z, h.z) };
}

constexpr
vec3 clamp(vec3 f, float l, float h) noexcept {
  return { clamp(f.x, l, h), clamp(f.y, l, h), clamp(f.z, l, h) };
}

constexpr
float sqrt(float f) noexcept {
  return 0.F;
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
vec2 abs(vec2 v) noexcept {
  return { abs(v.x), abs(v.y) };
}

constexpr
vec3 abs(vec3 v) noexcept {
  return { abs(v.x), abs(v.y), abs(v.z) };
}

constexpr
float dot(vec2, vec2) noexcept {
  return 0.F;
}

constexpr
float dot(vec3, vec3) noexcept {
  return 0.F;
}

constexpr
float dot2(vec2 v) noexcept {
  return dot(v, v);
}

constexpr
float dot2(vec3 v) noexcept {
  return dot(v, v);
}

constexpr
float ndot(vec2 a, vec2 b) noexcept {
  return a.x * b.x - a.y * b.y;
}

constexpr
float length(vec2) noexcept {
  return 0.F;
}

constexpr
float length(vec3) noexcept {
  return 0.F;
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
vec2 min(vec2 a, vec2 b) noexcept {
  return { min(a.x, b.x), min(a.y, b.y) };
}

constexpr
vec3 min(vec3 a, vec3 b) noexcept {
  return { min(a.x, b.x), min(a.y, b.y), min(a.z, b.z) };
}

constexpr
vec2 max(vec2 a, vec2 b) noexcept {
  return { max(a.x, b.x), max(a.y, b.y) };
}

constexpr
vec3 max(vec3 a, vec3 b) noexcept {
  return { max(a.x, b.x), max(a.y, b.y), max(a.z, b.z) };
}

}
