#pragma once

#include <core/tagged_type.hh>

#include <compare>
#include <concepts>

namespace flp::ColorTheory {

// HSV - Hue/Saturation/Value
// Cylindrical re-parameterization of SRGB
// Hue is an angle: [0, 360)
// Saturation and Value are [0,1]
// The Hue type may be identical to that from HSV: merge them?

struct HsvHueTag {};
struct HsvSaturationTag {};
struct HsvValueTag {};

template<std::floating_point Type = float>
struct HSV {
  using value_type = Type;

  using Hue        = TaggedType<Type, HsvHueTag>;
  using Saturation = TaggedType<Type, HsvSaturationTag>;
  using Value      = TaggedType<Type, HsvValueTag>;

  constexpr HSV() noexcept = default;
  constexpr HSV(Hue h, Saturation s, Value v) noexcept
    : hue(h)
    , saturation(s)
    , value(v)
  {}

  constexpr HSV(const HSV&) noexcept = default;
  constexpr HSV(HSV&&) noexcept      = default;

  constexpr HSV& operator=(const HSV&) noexcept = default;
  constexpr HSV& operator=(HSV&&) noexcept      = default;

  constexpr ~HSV() noexcept = default;

  constexpr friend auto operator<=>(const HSV&, const HSV&) noexcept = default;

  Hue        hue{};
  Saturation saturation{};
  Value      value{};
};

} // namespace flp::ColorTheory
