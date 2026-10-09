#pragma once

#include "color_theory/component.hh"

#include <bit>
#include <compare>
#include <cstdint>
#include <limits>

namespace flp::ColorTheory {

template<typename Type, template<typename...> typename ...Components>
struct Color : Components<Type>... {
  using value_type = Type;

  constexpr
  Color() = default;

  // accept normalized floating point values
  template<std::floating_point ...FTypes>
  constexpr
  Color(const FTypes& ...values)
    requires (sizeof...(FTypes) == sizeof...(Components))
    // that's...not right..
    : Components<Type>(static_cast<Type>(values * std::numeric_limits<Type>::max()))...
  {}

  // accept integral types not matching `Type`
  template<std::integral ...ITypes>
  constexpr
  Color(const ITypes& ...values)
    requires (sizeof...(ITypes) == sizeof...(Components))
    : Components<Type>(static_cast<Type>(values))...
  {}

  template<typename OType>
    requires (sizeof(OType) == sizeof(Color))
  constexpr
  Color(const OType& packed) {
    *this = std::bit_cast<Color>(packed);
  }

  template<template<typename...> typename ...OComponents>
    requires (sizeof...(OComponents) == sizeof...(Components))
  constexpr
  Color(const OComponents<Type>& ...components) {
    auto try_assign = [this] (const auto& ocomp) {
      using Other = std::remove_cvref_t<decltype(ocomp)>;

      static_cast<Other&>(*this).value_ = static_cast<const Other&>(ocomp).value_;
    };

    (try_assign(components), ...);
  }

  // color format interchange
  template<template<typename...> typename ...OComponents>
  constexpr
  Color(const Color<Type, OComponents...>& other) {
    auto try_assign = [this] (auto& ocomp) {
      using Other = std::remove_cvref_t<decltype(ocomp)>;

      static_cast<Other&>(*this).value_ = static_cast<const Other&>(ocomp).value_;
    };

    (try_assign(static_cast<const Components<Type>&>(other)), ...);
  }

  template<typename Packed>
    requires (sizeof(Packed) == sizeof...(Components) * sizeof(Type))
  constexpr
  Packed bit_value() const noexcept {
    return std::bit_cast<Packed>(*this);
  }

  template<typename Packed>
    requires (sizeof(Packed) == sizeof(Color))
  constexpr
  void bit_value(const Packed& packed) noexcept {
    *this = std::bit_cast<Color>(packed);
  }

  friend
  constexpr
  bool operator==(const Color&, const Color&) noexcept = default;

  friend
  constexpr
  auto operator<=>(const Color&, const Color&) noexcept = default;
};

template<typename Type, template<typename...> typename ...Components>
using RX = Color<Type, RedComponent, Components...>;

template<typename Type, template<typename...> typename ...Components>
using GX = Color<Type, GreenComponent, Components...>;

template<typename Type, template<typename...> typename ...Components>
using BX = Color<Type, BlueComponent, Components...>;

template<typename Type, template<typename...> typename ...Components>
using RGX = RX<Type, GreenComponent, Components...>;

template<typename Type, template<typename...> typename ...Components>
using BGX = BX<Type, GreenComponent, Components...>;

template<typename Type, template<typename...> typename ...Components>
using RGBX = Color<Type, RedComponent, GreenComponent, BlueComponent, Components...>;

}
