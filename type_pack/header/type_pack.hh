#pragma once

#include <core/traits.hh>

#include <concepts>
#include <cstddef>

namespace flp {

template<typename...>
struct TypePack;

namespace {

// implement uniquity in terms of filter?
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

template<template<typename> typename, typename ...>
struct FilterHelper;

template<template<typename> typename Predicate>
struct FilterHelper<Predicate> {
  using type = TypePack<>;
};

template<template<typename> typename Predicate, typename T1, typename ...Types>
struct FilterHelper<Predicate, T1, Types...> {
  using type = std::conditional_t<Predicate<T1>::value, typename TypePack<Types...>::Filter<Predicate>::Prepend<T1>, typename TypePack<Types...>::Filter<Predicate>>;
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

}

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

  /*template<typename... OtherTypes>
    requires(sizeof...(Types) == sizeof...(OtherTypes))
  static constexpr BoolConstant<(std::same_as<Types, OtherTypes> and ...)> Equal{};

  template<typename... OtherTypes>
    requires(sizeof...(Types) != sizeof...(OtherTypes))
  static constexpr BoolConstant<false> Equal{};*/

  static constexpr size_t Size = sizeof...(Types);

  static constexpr BoolConstant<Size == 0> Empty{};

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

  template<template<typename> typename Predicate>
  using Filter = FilterHelper<Predicate, Types...>::type;
};

} // namespace flp
