#pragma once

#include <color_theory/convert.hh>
#include <color_theory/linear_rgb/linear_rgb.hh>
#include <color_theory/srgb/srgb.hh>

#include <cmath>

namespace flp::ColorTheory {

// sRGB electro-optical / opto-electronic transfer function (IEC
// 61966-2-1), applied per-channel.
namespace detail {

template<std::floating_point Type>
constexpr Type srgb_channel_to_linear(Type channel) noexcept {
  constexpr Type threshold = Type(0.04045);
  if (channel <= threshold) {
    return channel / Type(12.92);
  }
  return std::pow((channel + Type(0.055)) / Type(1.055), Type(2.4));
}

template<std::floating_point Type>
constexpr Type linear_channel_to_srgb(Type channel) noexcept {
  constexpr Type threshold = Type(0.0031308);
  if (channel <= threshold) {
    return channel * Type(12.92);
  }
  return Type(1.055) * std::pow(channel, Type(1) / Type(2.4)) - Type(0.055);
}

} // namespace detail

template<std::floating_point Type>
struct ConversionEdge<SRGB<Type>> {
  using Parent = LinearRGB<Type>;

  static constexpr Parent to_parent(SRGB<Type> value) noexcept {
    using Linear = LinearRGB<Type>;
    return Linear{
      typename Linear::Red  (detail::srgb_channel_to_linear(Type(value.red))),
      typename Linear::Green(detail::srgb_channel_to_linear(Type(value.green))),
      typename Linear::Blue (detail::srgb_channel_to_linear(Type(value.blue))),
    };
  }

  static constexpr SRGB<Type> from_parent(Parent value) noexcept {
    return SRGB<Type>{
      typename SRGB<Type>::Red  (detail::linear_channel_to_srgb(Type(value.red))),
      typename SRGB<Type>::Green(detail::linear_channel_to_srgb(Type(value.green))),
      typename SRGB<Type>::Blue (detail::linear_channel_to_srgb(Type(value.blue))),
    };
  }
};

} // namespace flp::ColorTheory
