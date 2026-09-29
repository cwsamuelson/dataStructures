#pragma once

#include <algorithm>
#include <array>
#include <cmath>
#include <concepts>

// Shared math for the "cylindrical" re-parameterizations of SRGB (HSV, HSL,
// and any future relatives like HWB). Deliberately not part of any single
// color space's own directory: both `srgb_hsv.hh` and `srgb_hsl.hh` include
// this to avoid re-deriving the same hue computation and sector
// reconstruction twice.
namespace flp::ColorTheory::detail {

template<std::floating_point Type>
struct MaxMinDelta {
  Type max;
  Type min;
  Type delta;
};

template<std::floating_point Type>
constexpr MaxMinDelta<Type> rgb_max_min_delta(Type r, Type g, Type b) noexcept {
  const Type max = std::max({r, g, b});
  const Type min = std::min({r, g, b});
  return {max, min, max - min};
}

// Standard hue computation shared by HSV and HSL, given the channel values
// and their pre-computed max/delta. Returns degrees in [0, 360).
template<std::floating_point Type>
constexpr Type rgb_hue(Type r, Type g, Type b, const MaxMinDelta<Type>& mmd) noexcept {
  if (mmd.delta == Type(0)) {
    return Type(0);
  }

  Type hue{};
  if (mmd.max == r) {
    hue = Type(60) * std::fmod((g - b) / mmd.delta, Type(6));
  } else if (mmd.max == g) {
    hue = Type(60) * (((b - r) / mmd.delta) + Type(2));
  } else {
    hue = Type(60) * (((r - g) / mmd.delta) + Type(4));
  }

  if (hue < Type(0)) {
    hue += Type(360);
  }
  return hue;
}

// Reconstructs an (r, g, b) triple (still missing the lightness/value
// offset `m`, which the caller adds) from hue and chroma, per the standard
// HSV/HSL "sector" formula.
template<std::floating_point Type>
constexpr std::array<Type, 3> hue_chroma_to_rgb(Type hue, Type chroma) noexcept {
  const Type x = chroma * (Type(1) - std::abs(std::fmod(hue / Type(60), Type(2)) - Type(1)));

  const int sector = static_cast<int>(std::fmod(hue, Type(360)) / Type(60));
  switch (sector) {
    case 0:  return {chroma, x, Type(0)};
    case 1:  return {x, chroma, Type(0)};
    case 2:  return {Type(0), chroma, x};
    case 3:  return {Type(0), x, chroma};
    case 4:  return {x, Type(0), chroma};
    default: return {chroma, Type(0), x};
  }
}

} // namespace flp::ColorTheory::detail
