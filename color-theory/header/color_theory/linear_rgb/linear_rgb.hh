#pragma once

#include <core/tagged_type.hh>

#include <compare>
#include <concepts>

namespace flp::ColorTheory {

// Linear-light RGB
// Uses the same primaries/white point as sRGB
// Most correct space to apply color math to (sRGB must be linearized first)

struct LinearRgbRedTag {};
struct LinearRgbGreenTag {};
struct LinearRgbBlueTag {};

template<std::floating_point Type = float>
struct LinearRGB {
  using value_type = Type;

  using Red   = TaggedType<Type, LinearRgbRedTag>;
  using Green = TaggedType<Type, LinearRgbGreenTag>;
  using Blue  = TaggedType<Type, LinearRgbBlueTag>;

  constexpr LinearRGB() noexcept = default;
  constexpr LinearRGB(Red r, Green g, Blue b) noexcept
    : red(r)
    , green(g)
    , blue(b)
  {}

  constexpr LinearRGB(const LinearRGB&) noexcept = default;
  constexpr LinearRGB(LinearRGB&&) noexcept      = default;

  constexpr LinearRGB& operator=(const LinearRGB&) noexcept = default;
  constexpr LinearRGB& operator=(LinearRGB&&) noexcept      = default;

  constexpr ~LinearRGB() noexcept = default;

  constexpr friend auto operator<=>(const LinearRGB&, const LinearRGB&) noexcept = default;

  Red   red{};
  Green green{};
  Blue  blue{};
};

} // namespace flp::ColorTheory
