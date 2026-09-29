#pragma once

#include <color_theory/conversions/hsx_common.hh>
#include <color_theory/convert.hh>
#include <color_theory/hsl/hsl.hh>
#include <color_theory/srgb/srgb.hh>

#include <cmath>

namespace flp::ColorTheory {

// Standard max/min/delta-based RGB <-> HSL conversion.
template<std::floating_point Type>
struct ConversionEdge<HSL<Type>> {
  using Parent = SRGB<Type>;

  static constexpr Parent to_parent(HSL<Type> value) noexcept {
    const Type h = Type(value.hue);
    const Type s = Type(value.saturation);
    const Type l = Type(value.lightness);

    const Type chroma = (Type(1) - std::abs(Type(2) * l - Type(1))) * s;
    const auto rgb1    = detail::hue_chroma_to_rgb(h, chroma);
    const Type m        = l - chroma / Type(2);

    return Parent{
      typename Parent::Red  (rgb1[0] + m),
      typename Parent::Green(rgb1[1] + m),
      typename Parent::Blue (rgb1[2] + m),
    };
  }

  static constexpr HSL<Type> from_parent(Parent value) noexcept {
    const Type r = Type(value.red);
    const Type g = Type(value.green);
    const Type b = Type(value.blue);

    const auto mmd = detail::rgb_max_min_delta(r, g, b);
    const Type hue = detail::rgb_hue(r, g, b, mmd);
    const Type lightness = (mmd.max + mmd.min) / Type(2);
    const Type denom = Type(1) - std::abs(Type(2) * lightness - Type(1));
    const Type sat = (mmd.delta == Type(0)) ? Type(0) : (mmd.delta / denom);

    return HSL<Type>{
      typename HSL<Type>::Hue(hue),
      typename HSL<Type>::Saturation(sat),
      typename HSL<Type>::Lightness(lightness),
    };
  }
};

} // namespace flp::ColorTheory
