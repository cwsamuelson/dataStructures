#pragma once

#define SwizMember(TYPE, NAME) \
  constexpr \
  TYPE NAME() noexcept { \
    return { *this }; \
  }

#define Swiz2Type(Vec, name, x, y) \
  using name = XY<Vec, decltype(std::declval<Vec>().x), &Vec::x, &Vec::y>;
#define Swiz3Type(Vec, name, x, y, z) \
  using name = XYZ<Vec, decltype(std::declval<Vec>().x), &Vec::x, &Vec::y, &Vec::z>;
#define Swiz4Type(Vec, name, x, y, z, w) \
  using name = XYZW<Vec, decltype(std::declval<Vec>().x), &Vec::x, &Vec::y, &Vec::z, &Vec::w>;

/*!
 * @param Vec vecN host type
 * @param [xy] construct member name
 * @param [XY] construct member type
 */
#define Swiz2Types(x, y, X, Y, Vec) \
  Swiz2Type(Vec, X##Y, x, y)

/*!
 * @param Vec
 * @param [xyz]
 * @param [XYZ]
 */
#define Swiz3Types(x, y, z, X, Y, Z, Vec) \
  Swiz3Type(Vec, X##Y##Z, x, y, z)

/*!
 * @param Vec
 * @param [xyzw]
 * @param [XYZW]
 */
#define Swiz4Types(x, y, z, w, X, Y, Z, W, Vec) \
  Swiz4Type(Vec, X##Y##Z##W, x, y, z, w)

#define Swiz2MemberRemap(x, y, X, Y) \
  SwizMember(X##Y, x##y)

#define Swiz3MemberRemap(x, y, z, X, Y, Z) \
  SwizMember(X##Y##Z, x##y##z)

#define Swiz4MemberRemap(x, y, z, w, X, Y, Z, W) \
  SwizMember(X##Y##Z##W, x##y##z##w)

// 2D

// SwizN___M
// N - Available Components
// M - Arguments passed to macro

#define Swiz2Combo2(macro, ...) \
  macro(x, x, X, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, y, X, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, y, Y, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, x, Y, X __VA_OPT__(, ) __VA_ARGS__)

#define Swiz2Combo3(macro, ...) \
  macro(x, x, x, X, X, X  __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, x, y, X, X, Y  __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, y, x, X, Y, X  __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, y, y, X, Y, Y  __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, x, x, Y, X, X  __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, x, y, Y, X, Y  __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, y, x, Y, Y, X  __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, y, y, Y, Y, Y  __VA_OPT__(, ) __VA_ARGS__)

#define Swiz2Combo4(macro, ...) \
  macro(x, x, x, x, X, X, X, X  __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, x, x, y, X, X, X, Y  __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, x, y, x, X, X, Y, X  __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, x, y, y, X, X, Y, Y  __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, y, x, x, X, Y, X, X  __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, y, x, y, X, Y, X, Y  __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, y, y, x, X, Y, Y, X  __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, y, y, y, X, Y, Y, Y  __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, x, x, x, Y, X, X, X  __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, x, x, y, Y, X, X, Y  __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, x, y, x, Y, X, Y, X  __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, x, y, y, Y, X, Y, Y  __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, y, x, x, Y, Y, X, X  __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, y, x, y, Y, Y, X, Y  __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, y, y, x, Y, Y, Y, X  __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, y, y, y, Y, Y, Y, Y  __VA_OPT__(, ) __VA_ARGS__)

#define Swiz2All \
  Swiz2Combo2(Swiz2Types, vec2) \
  Swiz2Combo2(Swiz2MemberRemap) \
  Swiz2Combo3(Swiz3Types, vec2) \
  Swiz2Combo3(Swiz3MemberRemap) \
  Swiz2Combo4(Swiz4Types, vec2) \
  Swiz2Combo4(Swiz4MemberRemap)

// 3D

#define Swiz3Combo2(macro, ...) \
  macro(x, x, X, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, y, X, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, z, X, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, x, Y, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, y, Y, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, z, Y, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, x, Z, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, y, Z, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, z, Z, Z __VA_OPT__(, ) __VA_ARGS__)

#define Swiz3Combo3(macro, ...) \
  macro(x, x, x, X, X, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, x, y, X, X, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, x, z, X, X, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, y, x, X, Y, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, y, y, X, Y, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, y, z, X, Y, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, z, x, X, Z, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, z, y, X, Z, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, z, z, X, Z, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, x, x, Y, X, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, x, y, Y, X, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, x, z, Y, X, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, y, x, Y, Y, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, y, y, Y, Y, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, y, z, Y, Y, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, z, x, Y, Z, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, z, y, Y, Z, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, z, z, Y, Z, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, x, x, Z, X, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, x, y, Z, X, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, x, z, Z, X, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, y, x, Z, Y, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, y, y, Z, Y, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, y, z, Z, Y, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, z, x, Z, Z, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, z, y, Z, Z, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, z, z, Z, Z, Z __VA_OPT__(, ) __VA_ARGS__)

#define Swiz3Combo4(macro, ...) \
  macro(x, x, x, x, X, X, X, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, x, x, y, X, X, X, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, x, x, z, X, X, X, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, x, y, x, X, X, Y, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, x, y, y, X, X, Y, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, x, y, z, X, X, Y, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, x, z, x, X, X, Z, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, x, z, y, X, X, Z, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, x, z, z, X, X, Z, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, y, x, x, X, Y, X, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, y, x, y, X, Y, X, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, y, x, z, X, Y, X, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, y, y, x, X, Y, Y, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, y, y, y, X, Y, Y, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, y, y, z, X, Y, Y, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, y, z, x, X, Y, Z, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, y, z, y, X, Y, Z, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, y, z, z, X, Y, Z, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, z, x, x, X, Z, X, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, z, x, y, X, Z, X, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, z, x, z, X, Z, X, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, z, y, x, X, Z, Y, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, z, y, y, X, Z, Y, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, z, y, z, X, Z, Y, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, z, z, x, X, Z, Z, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, z, z, y, X, Z, Z, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, z, z, z, X, Z, Z, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, x, x, x, Y, X, X, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, x, x, y, Y, X, X, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, x, x, z, Y, X, X, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, x, y, x, Y, X, Y, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, x, y, y, Y, X, Y, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, x, y, z, Y, X, Y, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, x, z, x, Y, X, Z, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, x, z, y, Y, X, Z, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, x, z, z, Y, X, Z, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, y, x, x, Y, Y, X, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, y, x, y, Y, Y, X, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, y, x, z, Y, Y, X, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, y, y, x, Y, Y, Y, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, y, y, y, Y, Y, Y, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, y, y, z, Y, Y, Y, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, y, z, x, Y, Y, Z, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, y, z, y, Y, Y, Z, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, y, z, z, Y, Y, Z, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, z, x, x, Y, Z, X, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, z, x, y, Y, Z, X, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, z, x, z, Y, Z, X, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, z, y, x, Y, Z, Y, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, z, y, y, Y, Z, Y, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, z, y, z, Y, Z, Y, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, z, z, x, Y, Z, Z, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, z, z, y, Y, Z, Z, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, z, z, z, Y, Z, Z, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, x, x, x, Z, X, X, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, x, x, y, Z, X, X, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, x, x, z, Z, X, X, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, x, y, x, Z, X, Y, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, x, y, y, Z, X, Y, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, x, y, z, Z, X, Y, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, x, z, x, Z, X, Z, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, x, z, y, Z, X, Z, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, x, z, z, Z, X, Z, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, y, x, x, Z, Y, X, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, y, x, y, Z, Y, X, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, y, x, z, Z, Y, X, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, y, y, x, Z, Y, Y, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, y, y, y, Z, Y, Y, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, y, y, z, Z, Y, Y, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, y, z, x, Z, Y, Z, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, y, z, y, Z, Y, Z, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, y, z, z, Z, Y, Z, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, z, x, x, Z, Z, X, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, z, x, y, Z, Z, X, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, z, x, z, Z, Z, X, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, z, y, x, Z, Z, Y, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, z, y, y, Z, Z, Y, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, z, y, z, Z, Z, Y, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, z, z, x, Z, Z, Z, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, z, z, y, Z, Z, Z, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, z, z, z, Z, Z, Z, Z __VA_OPT__(, ) __VA_ARGS__)

#define Swiz3All \
  Swiz3Combo2(Swiz2Types, vec3) \
  Swiz3Combo2(Swiz2MemberRemap) \
  Swiz3Combo3(Swiz3Types, vec3) \
  Swiz3Combo3(Swiz3MemberRemap) \
  Swiz3Combo4(Swiz4Types, vec3) \
  Swiz3Combo4(Swiz4MemberRemap)

// 4D

#define Swiz4Combo2(macro, ...) \
  macro(x, x, X, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, y, X, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, z, X, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, w, X, W __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, x, Y, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, y, Y, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, z, Y, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, w, Y, W __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, x, Z, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, y, Z, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, z, Z, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, w, Z, W __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, x, W, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, y, W, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, z, W, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, w, W, W __VA_OPT__(, ) __VA_ARGS__)

#define Swiz4Combo3(macro, ...) \
  macro(x, x, x, X, X, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, x, y, X, X, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, x, z, X, X, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, x, w, X, X, w __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, y, x, X, Y, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, y, y, X, Y, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, y, z, X, Y, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, y, w, X, Y, w __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, z, x, X, Z, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, z, y, X, Z, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, z, z, X, Z, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, z, w, X, Z, w __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, w, x, X, W, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, w, y, X, W, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, w, z, X, W, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, w, w, X, W, w __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, x, x, Y, X, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, x, y, Y, X, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, x, z, Y, X, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, x, w, Y, X, w __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, y, x, Y, Y, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, y, y, Y, Y, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, y, z, Y, Y, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, y, w, Y, Y, w __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, z, x, Y, Z, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, z, y, Y, Z, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, z, z, Y, Z, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, z, w, Y, Z, w __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, w, x, Y, W, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, w, y, Y, W, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, w, z, Y, W, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, w, w, Y, W, w __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, x, x, Z, X, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, x, y, Z, X, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, x, z, Z, X, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, x, w, Z, X, w __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, y, x, Z, Y, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, y, y, Z, Y, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, y, z, Z, Y, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, y, w, Z, Y, w __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, z, x, Z, Z, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, z, y, Z, Z, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, z, z, Z, Z, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, z, w, Z, Z, w __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, w, x, Z, W, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, w, y, Z, W, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, w, z, Z, W, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, w, w, Z, W, w __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, x, x, W, X, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, x, y, W, X, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, x, z, W, X, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, x, w, W, X, w __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, y, x, W, Y, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, y, y, W, Y, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, y, z, W, Y, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, y, w, W, Y, w __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, z, x, W, Z, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, z, y, W, Z, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, z, z, W, Z, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, z, w, W, Z, w __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, w, x, W, W, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, w, y, W, W, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, w, z, W, W, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, w, w, W, W, w __VA_OPT__(, ) __VA_ARGS__)

#define Swiz4Combo4(macro, ...) \
  macro(x, x, x, x, X, X, X, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, x, x, y, X, X, X, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, x, x, z, X, X, X, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, x, x, w, X, X, X, W __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, x, y, x, X, X, Y, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, x, y, y, X, X, Y, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, x, y, z, X, X, Y, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, x, y, w, X, X, Y, W __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, x, z, x, X, X, Z, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, x, z, y, X, X, Z, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, x, z, z, X, X, Z, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, x, z, w, X, X, Z, W __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, x, w, x, X, X, W, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, x, w, y, X, X, W, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, x, w, z, X, X, W, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, x, w, w, X, X, W, W __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, y, x, x, X, Y, X, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, y, x, y, X, Y, X, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, y, x, z, X, Y, X, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, y, x, w, X, Y, X, W __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, y, y, x, X, Y, Y, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, y, y, y, X, Y, Y, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, y, y, z, X, Y, Y, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, y, y, w, X, Y, Y, W __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, y, z, x, X, Y, Z, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, y, z, y, X, Y, Z, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, y, z, z, X, Y, Z, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, y, z, w, X, Y, Z, W __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, y, w, x, X, Y, W, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, y, w, y, X, Y, W, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, y, w, z, X, Y, W, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, y, w, w, X, Y, W, W __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, z, x, x, X, Z, X, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, z, x, y, X, Z, X, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, z, x, z, X, Z, X, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, z, x, w, X, Z, X, W __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, z, y, x, X, Z, Y, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, z, y, y, X, Z, Y, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, z, y, z, X, Z, Y, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, z, y, w, X, Z, Y, W __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, z, z, x, X, Z, Z, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, z, z, y, X, Z, Z, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, z, z, z, X, Z, Z, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, z, z, w, X, Z, Z, W __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, z, w, x, X, Z, W, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, z, w, y, X, Z, W, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, z, w, z, X, Z, W, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, z, w, w, X, Z, W, W __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, w, x, x, X, W, X, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, w, x, y, X, W, X, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, w, x, z, X, W, X, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, w, x, w, X, W, X, W __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, w, y, x, X, W, Y, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, w, y, y, X, W, Y, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, w, y, z, X, W, Y, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, w, y, w, X, W, Y, W __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, w, z, x, X, W, Z, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, w, z, y, X, W, Z, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, w, z, z, X, W, Z, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, w, z, w, X, W, Z, W __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, w, w, x, X, W, W, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, w, w, y, X, W, W, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, w, w, z, X, W, W, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(x, w, w, w, X, W, W, W __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, x, x, x, Y, X, X, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, x, x, y, Y, X, X, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, x, x, z, Y, X, X, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, x, x, w, Y, X, X, W __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, x, y, x, Y, X, Y, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, x, y, y, Y, X, Y, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, x, y, z, Y, X, Y, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, x, y, w, Y, X, Y, W __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, x, z, x, Y, X, Z, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, x, z, y, Y, X, Z, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, x, z, z, Y, X, Z, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, x, z, w, Y, X, Z, W __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, x, w, x, Y, X, W, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, x, w, y, Y, X, W, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, x, w, z, Y, X, W, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, x, w, w, Y, X, W, W __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, y, x, x, Y, Y, X, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, y, x, y, Y, Y, X, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, y, x, z, Y, Y, X, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, y, x, w, Y, Y, X, W __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, y, y, x, Y, Y, Y, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, y, y, y, Y, Y, Y, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, y, y, z, Y, Y, Y, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, y, y, w, Y, Y, Y, W __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, y, z, x, Y, Y, Z, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, y, z, y, Y, Y, Z, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, y, z, z, Y, Y, Z, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, y, z, w, Y, Y, Z, W __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, y, w, x, Y, Y, W, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, y, w, y, Y, Y, W, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, y, w, z, Y, Y, W, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, y, w, w, Y, Y, W, W __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, z, x, x, Y, Z, X, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, z, x, y, Y, Z, X, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, z, x, z, Y, Z, X, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, z, x, w, Y, Z, X, W __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, z, y, x, Y, Z, Y, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, z, y, y, Y, Z, Y, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, z, y, z, Y, Z, Y, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, z, y, w, Y, Z, Y, W __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, z, z, x, Y, Z, Z, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, z, z, y, Y, Z, Z, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, z, z, z, Y, Z, Z, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, z, z, w, Y, Z, Z, W __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, z, w, x, Y, Z, W, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, z, w, y, Y, Z, W, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, z, w, z, Y, Z, W, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, z, w, w, Y, Z, W, W __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, w, x, x, Y, W, X, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, w, x, y, Y, W, X, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, w, x, z, Y, W, X, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, w, x, w, Y, W, X, W __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, w, y, x, Y, W, Y, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, w, y, y, Y, W, Y, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, w, y, z, Y, W, Y, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, w, y, w, Y, W, Y, W __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, w, z, x, Y, W, Z, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, w, z, y, Y, W, Z, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, w, z, z, Y, W, Z, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, w, z, w, Y, W, Z, W __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, w, w, x, Y, W, W, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, w, w, y, Y, W, W, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, w, w, z, Y, W, W, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(y, w, w, w, Y, W, W, W __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, x, x, x, Z, X, X, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, x, x, y, Z, X, X, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, x, x, z, Z, X, X, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, x, x, w, Z, X, X, W __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, x, y, x, Z, X, Y, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, x, y, y, Z, X, Y, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, x, y, z, Z, X, Y, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, x, y, w, Z, X, Y, W __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, x, z, x, Z, X, Z, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, x, z, y, Z, X, Z, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, x, z, z, Z, X, Z, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, x, z, w, Z, X, Z, W __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, x, w, x, Z, X, W, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, x, w, y, Z, X, W, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, x, w, z, Z, X, W, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, x, w, w, Z, X, W, W __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, y, x, x, Z, Y, X, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, y, x, y, Z, Y, X, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, y, x, z, Z, Y, X, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, y, x, w, Z, Y, X, W __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, y, y, x, Z, Y, Y, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, y, y, y, Z, Y, Y, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, y, y, z, Z, Y, Y, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, y, y, w, Z, Y, Y, W __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, y, z, x, Z, Y, Z, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, y, z, y, Z, Y, Z, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, y, z, z, Z, Y, Z, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, y, z, w, Z, Y, Z, W __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, y, w, x, Z, Y, W, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, y, w, y, Z, Y, W, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, y, w, z, Z, Y, W, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, y, w, w, Z, Y, W, W __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, z, x, x, Z, Z, X, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, z, x, y, Z, Z, X, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, z, x, z, Z, Z, X, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, z, x, w, Z, Z, X, W __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, z, y, x, Z, Z, Y, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, z, y, y, Z, Z, Y, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, z, y, z, Z, Z, Y, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, z, y, w, Z, Z, Y, W __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, z, z, x, Z, Z, Z, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, z, z, y, Z, Z, Z, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, z, z, z, Z, Z, Z, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, z, z, w, Z, Z, Z, W __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, z, w, x, Z, Z, W, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, z, w, y, Z, Z, W, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, z, w, z, Z, Z, W, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, z, w, w, Z, Z, W, W __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, w, x, x, Z, W, X, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, w, x, y, Z, W, X, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, w, x, z, Z, W, X, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, w, x, w, Z, W, X, W __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, w, y, x, Z, W, Y, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, w, y, y, Z, W, Y, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, w, y, z, Z, W, Y, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, w, y, w, Z, W, Y, W __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, w, z, x, Z, W, Z, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, w, z, y, Z, W, Z, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, w, z, z, Z, W, Z, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, w, z, w, Z, W, Z, W __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, w, w, x, Z, W, W, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, w, w, y, Z, W, W, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, w, w, z, Z, W, W, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(z, w, w, w, Z, W, W, W __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, x, x, x, W, X, X, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, x, x, y, W, X, X, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, x, x, z, W, X, X, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, x, x, w, W, X, X, W __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, x, y, x, W, X, Y, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, x, y, y, W, X, Y, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, x, y, z, W, X, Y, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, x, y, w, W, X, Y, W __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, x, z, x, W, X, Z, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, x, z, y, W, X, Z, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, x, z, z, W, X, Z, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, x, z, w, W, X, Z, W __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, x, w, x, W, X, W, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, x, w, y, W, X, W, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, x, w, z, W, X, W, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, x, w, w, W, X, W, W __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, y, x, x, W, Y, X, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, y, x, y, W, Y, X, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, y, x, z, W, Y, X, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, y, x, w, W, Y, X, W __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, y, y, x, W, Y, Y, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, y, y, y, W, Y, Y, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, y, y, z, W, Y, Y, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, y, y, w, W, Y, Y, W __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, y, z, x, W, Y, Z, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, y, z, y, W, Y, Z, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, y, z, z, W, Y, Z, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, y, z, w, W, Y, Z, W __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, y, w, x, W, Y, W, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, y, w, y, W, Y, W, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, y, w, z, W, Y, W, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, y, w, w, W, Y, W, W __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, z, x, x, W, Z, X, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, z, x, y, W, Z, X, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, z, x, z, W, Z, X, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, z, x, w, W, Z, X, W __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, z, y, x, W, Z, Y, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, z, y, y, W, Z, Y, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, z, y, z, W, Z, Y, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, z, y, w, W, Z, Y, W __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, z, z, x, W, Z, Z, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, z, z, y, W, Z, Z, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, z, z, z, W, Z, Z, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, z, z, w, W, Z, Z, W __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, z, w, x, W, Z, W, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, z, w, y, W, Z, W, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, z, w, z, W, Z, W, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, z, w, w, W, Z, W, W __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, w, x, x, W, W, X, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, w, x, y, W, W, X, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, w, x, z, W, W, X, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, w, x, w, W, W, X, W __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, w, y, x, W, W, Y, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, w, y, y, W, W, Y, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, w, y, z, W, W, Y, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, w, y, w, W, W, Y, W __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, w, z, x, W, W, Z, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, w, z, y, W, W, Z, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, w, z, z, W, W, Z, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, w, z, w, W, W, Z, W __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, w, w, x, W, W, W, X __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, w, w, y, W, W, W, Y __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, w, w, z, W, W, W, Z __VA_OPT__(, ) __VA_ARGS__) \
  macro(w, w, w, w, W, W, W, W __VA_OPT__(, ) __VA_ARGS__)

#define Swiz4All \
  Swiz4Combo2(Swiz2Types, vec4) \
  Swiz4Combo2(Swiz2MemberRemap) \
  Swiz4Combo3(Swiz3Types, vec4) \
  Swiz4Combo3(Swiz3MemberRemap) \
  Swiz4Combo4(Swiz4Types, vec4) \
  Swiz4Combo4(Swiz4MemberRemap)
