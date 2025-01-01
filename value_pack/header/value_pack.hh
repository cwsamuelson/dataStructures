#pragma once

#include <core/traits.hh>

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

  template<auto Value>
  using Prepend = ValuePack<Value, Values...>;

  template<auto Value>
  using Append = ValuePack<Values..., Value>;

  template<template<auto, auto> typename Functor, auto Value>
  static constexpr BoolConstant<(Functor<Value, Values>::value or ...)> AnyOf {};

  template<template<auto, auto> typename Functor, auto Value>
  static constexpr BoolConstant<(Functor<Value, Values>::value and ...)> AllOf {};

  template<auto Value>
  static constexpr auto Contains = AnyOf<Equality, Value>;

  template<template<auto, auto> typename Functor, auto... OtherValues>
  static constexpr auto Zip = (Functor<Values, OtherValues...>::value, ...);
};

} // namespace flp
