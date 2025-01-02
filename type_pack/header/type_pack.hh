#pragma once

#include <core/traits.hh>

#include <concepts>

namespace flp {

template<typename... Types>
struct TypePack {
  template<typename... OtherTypes>
    requires(sizeof...(Types) == sizeof...(OtherTypes))
  [[nodiscard]]
  constexpr bool operator==(const TypePack<OtherTypes...>&) const {
    return (std::same_as<Types, OtherTypes> && ...);
  }

  template<typename... OtherTypes>
    requires(sizeof...(Types) != sizeof...(OtherTypes))
  [[nodiscard]]
  constexpr bool operator==(const TypePack<OtherTypes...>&) const {
    return false;
  }

  template<typename Type>
  using Prepend = TypePack<Type, Types...>;

  template<typename Type>
  using Append = TypePack<Types..., Type>;

  template<template<typename> typename Predicate>
  static constexpr BoolConstant<(Predicate<Types>::value or ...)> AnyOf {};

  template<template<typename> typename Predicate>
  static constexpr BoolConstant<(Predicate<Types>::value and ...)> AllOf {};

  template<template<typename> typename Predicate>
  using Transform = TypePack<typename Predicate<Types>::type...>;
};

} // namespace flp
