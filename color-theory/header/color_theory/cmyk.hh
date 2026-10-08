#pragma once

#include <core/tagged_type.hh>

#include <compare>
#include <concepts>

namespace flp::ColorTheory {

// Cyan/Magenta/Yellow/Key(black), naive subtractive model off `SRGB`.
//!@NOTE a real CMYK model is specific to the printer/ink in use.
// This means there's no 'canonical' CMYK color-space.
// This uses a typical K=1-max(r,g,b) approximation.
// Don't use for 'real' CMYK/inking use
//!@TODO make conversion parameterizable

struct CmykCyanTag {};
struct CmykMagentaTag {};
struct CmykYellowTag {};
struct CmykKeyTag {};

template<std::floating_point Type = float>
struct CMYK {
  using value_type = Type;

  using Cyan    = TaggedType<Type, CmykCyanTag>;
  using Magenta = TaggedType<Type, CmykMagentaTag>;
  using Yellow  = TaggedType<Type, CmykYellowTag>;
  using Key     = TaggedType<Type, CmykKeyTag>;

  constexpr CMYK() noexcept = default;
  constexpr CMYK(Cyan c, Magenta m, Yellow y, Key k) noexcept
    : cyan(c)
    , magenta(m)
    , yellow(y)
    , key(k)
  {}

  constexpr CMYK(const CMYK&) noexcept = default;
  constexpr CMYK(CMYK&&) noexcept      = default;

  constexpr CMYK& operator=(const CMYK&) noexcept = default;
  constexpr CMYK& operator=(CMYK&&) noexcept      = default;

  constexpr ~CMYK() noexcept = default;

  constexpr friend auto operator<=>(const CMYK&, const CMYK&) noexcept = default;

  Cyan    cyan{};
  Magenta magenta{};
  Yellow  yellow{};
  Key     key{};
};

} // namespace flp::ColorTheory
