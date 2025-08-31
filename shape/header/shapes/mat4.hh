#pragma once

#include <array>

namespace flp {

struct mat4 {
  constexpr
  mat4(const std::array<std::array<float, 4>, 4>&)
  {}

  constexpr
  mat4(const std::array<vec4, 4>&)
  {}

  constexpr
  mat4(const vec4&, const vec4&)
  {}

  std::array<std::array<float, 4>, 4> values;
};

constexpr
vec4 operator*(const mat4&, const vec4&) noexcept {
}

}
