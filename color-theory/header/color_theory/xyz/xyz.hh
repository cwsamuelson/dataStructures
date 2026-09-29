#pragma once

#include <core/tagged_type.hh>

#include <compare>
#include <concepts>

namespace flp::ColorTheory {

// CIE 1931 XYZ tristimulus values
// D65 white point (Xn=0.95047, Yn=1.0, Zn=1.08883).
// Device-independent
// This is effectively the 'canonical' color space, and is typically used to define other color spaces.
// Therefore it is the 'hub' or central space ultimately leveraged to convert color spaces between each other.

struct XyzXTag {};
struct XyzYTag {};
struct XyzZTag {};

template<std::floating_point Type = float>
struct XYZ {
  using value_type = Type;

  using X = TaggedType<Type, XyzXTag>;
  using Y = TaggedType<Type, XyzYTag>;
  using Z = TaggedType<Type, XyzZTag>;

  constexpr XYZ() noexcept = default;
  constexpr XYZ(X x, Y y, Z z) noexcept
    : x(x)
    , y(y)
    , z(z)
  {}

  constexpr XYZ(const XYZ&) noexcept = default;
  constexpr XYZ(XYZ&&) noexcept      = default;

  constexpr XYZ& operator=(const XYZ&) noexcept = default;
  constexpr XYZ& operator=(XYZ&&) noexcept      = default;

  constexpr ~XYZ() noexcept = default;

  constexpr friend auto operator<=>(const XYZ&, const XYZ&) noexcept = default;

  X x{};
  Y y{};
  Z z{};
};

} // namespace flp::ColorTheory
