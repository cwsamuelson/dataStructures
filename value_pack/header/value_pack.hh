#pragma once

#include <core/traits.hh>

#include <array>
#include <concepts>
#include <cstddef>

namespace flp {

template<auto... Values>
struct ValuePack {
  template<auto... OtherValues>
    requires(sizeof...(Values) == sizeof...(OtherValues))
  [[nodiscard]]
  constexpr bool operator==(const ValuePack<OtherValues...>& other) const noexcept {
    return ((Values == OtherValues) and ...);
  }

  template<auto... OtherValues>
    requires(sizeof...(Values) != sizeof...(OtherValues))
  [[nodiscard]]
  constexpr bool operator==(const ValuePack<OtherValues...>& other) const noexcept {
    return false;
  }

  // Size

  template<auto Value>
  using Prepend = ValuePack<Value, Values...>;

  template<auto Value>
  using Append = ValuePack<Values..., Value>;

  template<template<auto> typename Predicate>
  static constexpr BoolConstant<(Predicate<Values>::value or ...)> AnyOf {};

  template<template<auto> typename Predicate>
  static constexpr BoolConstant<(Predicate<Values>::value and ...)> AllOf {};

  template<template<auto> typename Predicate>
  using Transform = ValuePack<Predicate<Values>::value...>;

  // Front
  // Back

  // Contains?
  // Zip?
};

} // namespace flp
