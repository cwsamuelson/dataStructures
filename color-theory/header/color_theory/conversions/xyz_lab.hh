#pragma once

#include <color_theory/convert.hh>
#include <color_theory/lab/lab.hh>
#include <color_theory/xyz/xyz.hh>

#include <cmath>

namespace flp::ColorTheory {

// Standard CIE XYZ <-> L*a*b* transform, D65 reference white
// (Xn=0.95047, Yn=1.0, Zn=1.08883), using the CIE's own piecewise
// definition (avoids the discontinuity a naive cube-root-only formula has
// near black).
namespace detail {

template<std::floating_point Type>
inline constexpr Type lab_epsilon = Type(216) / Type(24389); // (6/29)^3
template<std::floating_point Type>
inline constexpr Type lab_kappa   = Type(24389) / Type(27);  // 29^3 / 3^3

template<std::floating_point Type>
inline constexpr Type xyz_d65_xn = Type(0.95047);
template<std::floating_point Type>
inline constexpr Type xyz_d65_yn = Type(1.0);
template<std::floating_point Type>
inline constexpr Type xyz_d65_zn = Type(1.08883);

template<std::floating_point Type>
constexpr Type lab_forward(Type t) noexcept {
  if (t > lab_epsilon<Type>) {
    return std::cbrt(t);
  }
  return (lab_kappa<Type> * t + Type(16)) / Type(116);
}

template<std::floating_point Type>
constexpr Type lab_inverse(Type t) noexcept {
  const Type cubed = t * t * t;
  if (cubed > lab_epsilon<Type>) {
    return cubed;
  }
  return (Type(116) * t - Type(16)) / lab_kappa<Type>;
}

} // namespace detail

template<std::floating_point Type>
struct ConversionEdge<Lab<Type>> {
  using Parent = XYZ<Type>;

  static constexpr Parent to_parent(Lab<Type> value) noexcept {
    const Type fy = (Type(value.l) + Type(16)) / Type(116);
    const Type fx = fy + Type(value.a) / Type(500);
    const Type fz = fy - Type(value.b) / Type(200);

    return Parent{
      typename Parent::X(detail::xyz_d65_xn<Type> * detail::lab_inverse(fx)),
      typename Parent::Y(detail::xyz_d65_yn<Type> * detail::lab_inverse(fy)),
      typename Parent::Z(detail::xyz_d65_zn<Type> * detail::lab_inverse(fz)),
    };
  }

  static constexpr Lab<Type> from_parent(Parent value) noexcept {
    const Type fx = detail::lab_forward(Type(value.x) / detail::xyz_d65_xn<Type>);
    const Type fy = detail::lab_forward(Type(value.y) / detail::xyz_d65_yn<Type>);
    const Type fz = detail::lab_forward(Type(value.z) / detail::xyz_d65_zn<Type>);

    using L = Lab<Type>;
    return L{
      typename L::Lightness(Type(116) * fy - Type(16)),
      typename L::A(Type(500) * (fx - fy)),
      typename L::B(Type(200) * (fy - fz)),
    };
  }
};

} // namespace flp::ColorTheory
