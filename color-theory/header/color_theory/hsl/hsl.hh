#pragma once

#include <core/tagged_type.hh>

#include <compare>
#include <concepts>

namespace flp::ColorTheory {

// HSL - Hue/Saturation/Lightness
// Cylindrical re-parameterization of SRGB
// Hue is an angle: [0, 360)
// Saturation and Lightness are [0,1]
// The Hue type may be identical to that from HSV: merge them?

struct HslHueTag {};
struct HslSaturationTag {};
struct HslLightnessTag {};

template<std::floating_point Type = float>
struct HSL {
  using value_type = Type;

  using Hue        = TaggedType<Type, HslHueTag>;
  using Saturation = TaggedType<Type, HslSaturationTag>;
  using Lightness  = TaggedType<Type, HslLightnessTag>;

  constexpr HSL() noexcept = default;
  constexpr HSL(Hue h, Saturation s, Lightness l) noexcept
    : hue(h)
    , saturation(s)
    , lightness(l)
  {}

  constexpr HSL(const HSL&) noexcept = default;
  constexpr HSL(HSL&&) noexcept      = default;

  constexpr HSL& operator=(const HSL&) noexcept = default;
  constexpr HSL& operator=(HSL&&) noexcept      = default;

  constexpr ~HSL() noexcept = default;

  constexpr friend auto operator<=>(const HSL&, const HSL&) noexcept = default;

  Hue        hue{};
  Saturation saturation{};
  Lightness  lightness{};
};

} // namespace flp::ColorTheory
