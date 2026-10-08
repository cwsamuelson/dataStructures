#pragma once

#include <core/tagged_type.hh>

#include <compare>
#include <concepts>

namespace flp::ColorTheory {

// CIE L*a*b*, D65 reference white.
// Perceptually-uniform-ish device independent space

struct LabLightnessTag {};
struct LabATag {};
struct LabBTag {};

template<std::floating_point Type = float>
struct Lab {
  using value_type = Type;

  using Lightness = TaggedType<Type, LabLightnessTag>;
  using A         = TaggedType<Type, LabATag>;
  using B         = TaggedType<Type, LabBTag>;

  constexpr Lab() noexcept = default;
  constexpr Lab(Lightness l, A a, B b) noexcept
    : l(l)
    , a(a)
    , b(b)
  {}

  constexpr Lab(const Lab&) noexcept = default;
  constexpr Lab(Lab&&) noexcept      = default;

  constexpr Lab& operator=(const Lab&) noexcept = default;
  constexpr Lab& operator=(Lab&&) noexcept      = default;

  constexpr ~Lab() noexcept = default;

  constexpr friend auto operator<=>(const Lab&, const Lab&) noexcept = default;

  Lightness l{};
  A         a{};
  B         b{};
};

} // namespace flp::ColorTheory
