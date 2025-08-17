#pragma once

namespace flp {

struct vec2 {
  //Swiz2(vec2, 2)
  //Swiz3(vec2, 2)

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

  // swizzling!
  // It's frankly a smidge obnoxious
  //constexpr
  //XX2 xx() const noexcept;
  //constexpr
  //XY2 xy() const noexcept;
  //constexpr
  //YZ2 yx() const noexcept;
  //constexpr
  //YY2 yy() const noexcept;

  //constexpr
  //XXX2 xxx() const noexcept;
  //constexpr
  //XXY2 xxy() const noexcept;
  //constexpr
  //vec3 xyx() const noexcept;
  //constexpr
  //vec3 xyy() const noexcept;

  //constexpr
  //vec3 yxx() const noexcept;
  //constexpr
  //vec3 yxy() const noexcept;
  //constexpr
  //vec3 yyx() const noexcept;
  //constexpr
  //vec3 yyy() const noexcept;

  friend auto operator<=>(const vec2&, const vec2&) noexcept = default;
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
