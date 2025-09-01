#pragma once

#include "shapes/vec.hh"

#include <array>

namespace flp {

struct mat2x2 {
  constexpr
  mat2x2(const float A, const float B, const float C, const float D) noexcept
    : values{{ { A, B }, { C, D } }}
  {}

  constexpr
  mat2x2(const std::array<std::array<float, 2>, 2>&) noexcept
  {}

  constexpr
  mat2x2(const std::array<float, 4>&) noexcept
  {}

  constexpr
  mat2x2(const std::array<fvec2, 2>&) noexcept
  {}

  constexpr
  mat2x2(const fvec2&, const fvec2&) noexcept
  {}

  std::array<std::array<float, 2>, 2> values;
};

constexpr
fvec2 operator*(const mat2x2& mat, const fvec2& vec) noexcept {
  // | A B |   | E |   | A * E + B * F |
  // | C D | x | F | = | C * E + D * F |

  // const auto A = mat.values[0][0];
  // const auto B = mat.values[0][1];
  // const auto C = mat.values[1][0];
  // const auto D = mat.values[1][1];
  // const auto E = vec.x;
  // const auto F = vec.y;

  // return { A * E + B * F, C * E + D * F };

  return { mat.values[0][0] * vec.x() + mat.values[0][1] * vec.y(),
           mat.values[1][0] * vec.x() + mat.values[1][1] * vec.y() };
}

}
