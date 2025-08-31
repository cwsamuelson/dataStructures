#pragma once

#include "shapes/vecn.hh"

namespace flp {

template<typename Type>
struct vec2 : vecn<Type, 2> {
  using vec = vecn<Type, 2>;

  constexpr
  vec2() noexcept
    : vec2(0.f)
  {}

  constexpr
  vec2(const Type& value) noexcept
    : vec2(value, value)
  {}

  constexpr
  vec2(const Type& a, const Type& b) noexcept
    : vec(a, b)
    , x(vec::values[0])
    , y(vec::values[1])
  {}

  Type& x;
  Type& y;
  //Type& x = vec::values[0];
  //Type& y = vec::values[1];
};

template<typename Type>
struct vec3 : vecn<Type, 3> {
  using vec = vecn<Type, 3>;

  constexpr
  vec3()
    : vec3(0.f, 0.f, 0.f)
  {}

  constexpr
  vec3(const Type& value)
    : vec3(value, value, value)
  {}

  constexpr
  vec3(const Type a, const Type b, const Type c) noexcept
    : vec(a, b, c)
  {}

  Type& x = vec::values[0];
  Type& y = vec::values[1];
  Type& z = vec::values[2];
};

template<typename Type>
struct vec4 : vecn<Type, 4> {
  using vec = vecn<Type, 4>;

  constexpr
  vec4()
    : vec4(0.f, 0.f, 0.f, 0.f)
  {}

  constexpr
  vec4(const Type& value)
    : vec4(value, value, value, value)
  {}

  constexpr
  vec4(const Type a, const Type b, const Type c, const Type d) noexcept
    : vec(a, b, c, d)
  {}

  Type& x = vec::values[0];
  Type& y = vec::values[1];
  Type& z = vec::values[2];
  Type& w = vec::values[3];
};

using fvec2 = vec2<float>;
using fvec3 = vec3<float>;
using fvec4 = vec4<float>;

using dvec2 = vec2<double>;
using dvec3 = vec3<double>;
using dvec4 = vec4<double>;

using ivec2 = vec2<signed long long>;
using ivec3 = vec3<signed long long>;
using ivec4 = vec4<signed long long>;

using uvec2 = vec2<unsigned long long>;
using uvec3 = vec3<unsigned long long>;
using uvec4 = vec4<unsigned long long>;

using bvec2 = vec2<bool>;
using bvec3 = vec3<bool>;
using bvec4 = vec4<bool>;

}
