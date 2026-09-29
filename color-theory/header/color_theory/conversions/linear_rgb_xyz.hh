#pragma once

#include <color_theory/convert.hh>
#include <color_theory/linear_rgb/linear_rgb.hh>
#include <color_theory/xyz/xyz.hh>

namespace flp::ColorTheory {

// sRGB-primaries / D65-white-point 3x3 matrix (and its inverse), the
// standard linear-light-RGB <-> CIE XYZ transform.
template<std::floating_point Type>
struct ConversionEdge<LinearRGB<Type>> {
  using Parent = XYZ<Type>;

  static constexpr Parent to_parent(LinearRGB<Type> value) noexcept {
    const Type r = Type(value.red);
    const Type g = Type(value.green);
    const Type b = Type(value.blue);

    return Parent{
      typename Parent::X(Type(0.4124564) * r + Type(0.3575761) * g + Type(0.1804375) * b),
      typename Parent::Y(Type(0.2126729) * r + Type(0.7151522) * g + Type(0.0721750) * b),
      typename Parent::Z(Type(0.0193339) * r + Type(0.1191920) * g + Type(0.9503041) * b),
    };
  }

  static constexpr LinearRGB<Type> from_parent(Parent value) noexcept {
    const Type x = Type(value.x);
    const Type y = Type(value.y);
    const Type z = Type(value.z);

    using Linear = LinearRGB<Type>;
    return Linear{
      typename Linear::Red  (Type( 3.2404542) * x + Type(-1.5371385) * y + Type(-0.4985314) * z),
      typename Linear::Green(Type(-0.9692660) * x + Type( 1.8760108) * y + Type( 0.0415560) * z),
      typename Linear::Blue (Type( 0.0556434) * x + Type(-0.2040259) * y + Type( 1.0572252) * z),
    };
  }
};

} // namespace flp::ColorTheory
