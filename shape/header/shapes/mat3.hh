#pragma once

#include <array>

namespace flp {

struct mat3 {
  constexpr
  mat3(const std::array<std::array<float, 3>, 3>&) noexcept
  {}

  constexpr
  mat3(const std::array<vec3, 3>&) noexcept
  {}

  constexpr
  mat3(const vec3&, const vec3&) noexcept
  {}

  std::array<std::array<float, 3>, 3> values;
};

constexpr
vec3 operator*(const mat3&, const vec3&) noexcept {
}

}
