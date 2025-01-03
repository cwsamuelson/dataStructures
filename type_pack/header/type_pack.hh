#pragma once

#include <core/traits.hh>

#include <concepts>
#include <cstddef>

namespace flp {

template<typename...>
struct TypePack;

template<typename ...>
struct UniqueHelper;

template<>
struct UniqueHelper<> {
  using type = TypePack<>;
};

template<typename T1, typename ...Types>
struct UniqueHelper<T1, Types...> {
  static constexpr bool contains = (std::same_as<T1, Types> or ...);

  using type = std::conditional_t<contains, typename TypePack<Types...>::Unique, typename TypePack<Types...>::Unique::Prepend<T1>>;
};

template<typename...>
struct FrontHelper;

template<>
struct FrontHelper<> {
  using type = void;
};

template<typename T1, typename ...Types>
struct FrontHelper<T1, Types...> {
  using type = T1;
};

template<typename...>
struct BackHelper;

template<>
struct BackHelper<> {
  using type = void;
};

template<typename Type>
struct BackHelper<Type> {
  using type = Type;
};

template<typename T1, typename ...Types>
struct BackHelper<T1, Types...> {
  using type = typename BackHelper<Types...>::type;
};

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

  static constexpr size_t Size = sizeof...(Types);

  static constexpr size_t Empty = Size == 0;

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

  template<template<typename...> typename Target>
  using Rebind = Target<Types...>;

  using Front = typename FrontHelper<Types...>::type;
  using Back = typename BackHelper<Types...>::type;

  using Unique = UniqueHelper<Types...>::type;
};

} // namespace flp
