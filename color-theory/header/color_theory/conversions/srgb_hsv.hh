#pragma once

#include <color_theory/conversions/hsx_common.hh>
#include <color_theory/convert.hh>
#include <color_theory/hsv/hsv.hh>
#include <color_theory/srgb/srgb.hh>

namespace flp::ColorTheory {

// Standard max/min/delta-based RGB <-> HSV conversion.
template<std::floating_point Type>
struct ConversionEdge<HSV<Type>> {
  using Parent = SRGB<Type>;

  static constexpr Parent to_parent(HSV<Type> value) noexcept {
    const Type h = Type(value.hue);
    const Type s = Type(value.saturation);
    const Type v = Type(value.value);

    const Type chroma = v * s;
    const auto rgb1    = detail::hue_chroma_to_rgb(h, chroma);
    const Type m        = v - chroma;

    return Parent{
      typename Parent::Red  (rgb1[0] + m),
      typename Parent::Green(rgb1[1] + m),
      typename Parent::Blue (rgb1[2] + m),
    };
  }

  static constexpr HSV<Type> from_parent(Parent value) noexcept {
    const Type r = Type(value.red);
    const Type g = Type(value.green);
    const Type b = Type(value.blue);

    const auto mmd = detail::rgb_max_min_delta(r, g, b);
    const Type hue = detail::rgb_hue(r, g, b, mmd);
    const Type sat = (mmd.max > Type(0)) ? (mmd.delta / mmd.max) : Type(0);

    return HSV<Type>{
      typename HSV<Type>::Hue(hue),
      typename HSV<Type>::Saturation(sat),
      typename HSV<Type>::Value(mmd.max),
    };
  }
};

} // namespace flp::ColorTheory
