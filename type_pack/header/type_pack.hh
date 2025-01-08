#pragma once

#include <core/traits.hh>

#include <concepts>
#include <cstddef>

namespace flp {

template<typename...>
struct TypePack;

namespace {

// implement uniquity in terms of filter?
template<typename...>
struct UniqueHelper;

template<>
struct UniqueHelper<> {
  using type = TypePack<>;
};

template<typename T1, typename... Types>
struct UniqueHelper<T1, Types...> {
  static constexpr bool contains = (std::same_as<T1, Types> or ...);

  using type = std::
    conditional_t<contains, typename TypePack<Types...>::Unique, typename TypePack<Types...>::Unique::Prepend<T1>>;
};

template<template<typename> typename, typename...>
struct FilterHelper;

template<template<typename> typename Predicate>
struct FilterHelper<Predicate> {
  using type = TypePack<>;
};

template<template<typename> typename Predicate, typename T1, typename... Types>
struct FilterHelper<Predicate, T1, Types...> {
  using type = std::conditional_t<Predicate<T1>::value,
                                  typename TypePack<Types...>::Filter<Predicate>::Prepend<T1>,
                                  typename TypePack<Types...>::Filter<Predicate>>;
};

template<typename...>
struct FrontHelper;

template<>
struct FrontHelper<> {
  using type = void;
};

template<typename T1, typename... Types>
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

template<typename T1, typename... Types>
struct BackHelper<T1, Types...> {
  using type = typename BackHelper<Types...>::type;
};

template<typename... Types>
struct LShiftHelper;

template<>
struct LShiftHelper<> {
  using type = TypePack<>;
};

template<typename V1, typename... Types>
struct LShiftHelper<V1, Types...> {
  using type = TypePack<Types..., V1>;
};

template<typename... Types>
struct RShiftHelper;

template<>
struct RShiftHelper<> {
  using type = TypePack<>;
};

template<typename Left, typename Right>
struct RShiftHelper<Left, Right> {
  using type = TypePack<Right, Left>;
};

template<typename V1, typename... Types>
struct RShiftHelper<V1, Types...> {
  using type = typename RShiftHelper<Types...>::type;
};

template<size_t Count, typename... Types>
struct TakeHelper;

template<typename... Types>
struct TakeHelper<0, Types...> {
  using type = TypePack<>;
};

template<size_t Count, typename Type, typename... Types>
  requires(Count > 1)
struct TakeHelper<Count, Type, Types...> {
  using type = typename TakeHelper<Count - 1, Types...>::type::template Prepend<Type>;
};

template<typename Type, typename... Types>
struct TakeHelper<1, Type, Types...> {
  using type = TypePack<Type>;
};

template<size_t Count, typename... Types>
struct DropHelper;

template<typename... Types>
struct DropHelper<0, Types...> {
  using type = TypePack<Types...>;
};

template<typename Type, typename... Types>
struct DropHelper<1, Type, Types...> {
  using type = TypePack<Types...>;
};

template<size_t Count, typename Type, typename... Types>
  requires(Count > 1)
struct DropHelper<Count, Type, Types...> {
  using type = typename DropHelper<Count - 1, Types...>::type;
};

template<typename... Types>
struct ReverseHelper;

template<>
struct ReverseHelper<> {
  using type = TypePack<>;
};

template<typename Type>
struct ReverseHelper<Type> {
  using type = TypePack<Type>;
};

template<typename Type, typename... Types>
struct ReverseHelper<Type, Types...> {
  using type = typename ReverseHelper<Types...>::type::template Append<Type>;
};

} // namespace

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

  static constexpr BoolConstant<Size == 0> Empty {};

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
  using Back  = typename BackHelper<Types...>::type;

  using Unique = UniqueHelper<Types...>::type;

  template<template<typename> typename Predicate>
  using Filter = FilterHelper<Predicate, Types...>::type;

  //! @TODO shift by an amount
  using LeftShift  = typename LShiftHelper<Types...>::type;
  using RightShift = typename RShiftHelper<Types...>::type;

  template<size_t Count>
  using Take = typename TakeHelper<Count, Types...>::type;

  template<size_t Count>
  using Drop = typename DropHelper<Count, Types...>::type;

  using Reverse = typename ReverseHelper<Types...>::type;
};

} // namespace flp

