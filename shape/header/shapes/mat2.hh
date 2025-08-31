#pragma once

#include "shapes/vec2.hh"

#include <array>

namespace flp {

struct mat2 {
  constexpr
  mat2(const float A, const float B, const float C, const float D)
    : values{{ { A, B }, { C, D } }}
  {}

  constexpr
  mat2(const std::array<std::array<float, 2>, 2>&) noexcept
  {}

  constexpr
  mat2(const std::array<vec2, 2>&) noexcept
  {}

  constexpr
  mat2(const vec2&, const vec2&) noexcept
  {}

  std::array<std::array<float, 2>, 2> values;
};

constexpr
vec2 operator*(const mat2& mat, const vec2& vec) noexcept {
  // | A B |   | E |   | A * E + B * F |
  // | C D | x | F | = | C * E + D * F |

  // const auto A = mat.values[0][0];
  // const auto B = mat.values[0][1];
  // const auto C = mat.values[1][0];
  // const auto D = mat.values[1][1];
  // const auto E = vec.x;
  // const auto F = vec.y;

  // return { A * E + B * F, C * E + D * F };

  return { mat.values[0][0] * vec.x + mat.values[0][1] * vec.y, mat.values[1][0] * vec.x + mat.values[1][1] * vec.y };
}

}
