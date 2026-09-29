#pragma once

#include <core/tagged_type.hh>

#include <compare>
#include <concepts>

namespace flp::ColorTheory {

// Common, gamma-encoded "RGB" (IEC 61966-2-1)
// Not identical to LinearRGB, like one might assume

struct SrgbRedTag {};
struct SrgbGreenTag {};
struct SrgbBlueTag {};

template<std::floating_point Type = float>
struct SRGB {
  using value_type = Type;

  using Red   = TaggedType<Type, SrgbRedTag>;
  using Green = TaggedType<Type, SrgbGreenTag>;
  using Blue  = TaggedType<Type, SrgbBlueTag>;

  constexpr SRGB() noexcept = default;
  constexpr SRGB(Red r, Green g, Blue b) noexcept
    : red(r)
    , green(g)
    , blue(b)
  {}

  constexpr SRGB(const SRGB&) noexcept = default;
  constexpr SRGB(SRGB&&) noexcept      = default;

  constexpr SRGB& operator=(const SRGB&) noexcept = default;
  constexpr SRGB& operator=(SRGB&&) noexcept      = default;

  constexpr ~SRGB() noexcept = default;

  constexpr friend auto operator<=>(const SRGB&, const SRGB&) noexcept = default;

  Red   red{};
  Green green{};
  Blue  blue{};
};

} // namespace flp::ColorTheory
