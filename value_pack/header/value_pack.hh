#pragma once

#include <core/traits.hh>

#include <array>
#include <concepts>
#include <cstddef>

namespace flp {

template<auto...>
struct ValuePack;

namespace {

// implement uniquity in terms of filter?
template<auto...>
struct UniqueHelper;

template<>
struct UniqueHelper<> {
  using type = ValuePack<>;
};

template<auto V1, auto... Values>
struct UniqueHelper<V1, Values...> {
  static constexpr bool contains = ((V1 == Values) or ...);

  using type = std::
    conditional_t<contains, typename ValuePack<Values...>::Unique, typename ValuePack<Values...>::Unique::Prepend<V1>>;
};

template<template<auto> typename, auto...>
struct FilterHelper;

template<template<auto> typename Predicate>
struct FilterHelper<Predicate> {
  using type = ValuePack<>;
};

template<template<auto> typename Predicate, auto V1, auto... Values>
struct FilterHelper<Predicate, V1, Values...> {
  using type = std::conditional_t<Predicate<V1>::value,
                                  typename ValuePack<Values...>::Filter<Predicate>::Prepend<V1>,
                                  typename ValuePack<Values...>::Filter<Predicate>>;
};

template<auto...>
struct FrontHelper;

template<>
struct FrontHelper<> {};

template<auto V1, auto... Values>
struct FrontHelper<V1, Values...> {
  static constexpr auto value = V1;
};

template<auto...>
struct BackHelper;

template<>
struct BackHelper<> {};

template<auto Value>
struct BackHelper<Value> {
  static constexpr auto value = Value;
};

template<auto V1, auto... Values>
struct BackHelper<V1, Values...> {
  static constexpr auto value = BackHelper<Values...>::value;
};

template<auto... Values>
struct LShiftHelper;

template<>
struct LShiftHelper<> {
  using type = ValuePack<>;
};

template<auto V1, auto... Values>
struct LShiftHelper<V1, Values...> {
  using type = ValuePack<Values..., V1>;
};

template<auto... Values>
struct RShiftHelper;

template<>
struct RShiftHelper<> {
  using type = ValuePack<>;
};

template<auto Left, auto Right>
struct RShiftHelper<Left, Right> {
  using type = ValuePack<Right, Left>;
};

template<auto V1, auto... Values>
struct RShiftHelper<V1, Values...> {
  using type = typename RShiftHelper<Values...>::type;
};

template<size_t Count, auto... Values>
struct TakeHelper;

template<size_t Count, auto Value, auto... Values>
struct TakeHelper<Count, Value, Values...> {
  using type = typename TakeHelper<Count - 1, Values...>::type::template Prepend<Value>;
};

template<auto Value, auto... Values>
struct TakeHelper<1, Value, Values...> {
  using type = ValuePack<Value>;
};

template<size_t Count, auto... Values>
struct DropHelper;

template<size_t Count, auto Value, auto... Values>
struct DropHelper<Count, Value, Values...> {
  using type = typename DropHelper<Count - 1, Values...>::type;
};

template<auto Value, auto... Values>
struct DropHelper<1, Value, Values...> {
  using type = ValuePack<Values...>;
};

template<auto... Values>
struct ReverseHelper;

template<>
struct ReverseHelper<> {
  using type = ValuePack<>;
};

template<auto Value>
struct ReverseHelper<Value> {
  using type = ValuePack<Value>;
};

template<auto Value, auto... Values>
struct ReverseHelper<Value, Values...> {
  using type = typename ReverseHelper<Values...>::type::template Append<Value>;
};

} // namespace

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

  /*template<auto... OtherValues>
    requires(sizeof...(Values) == sizeof...(OtherValues))
  static constexpr BoolConstant<( and ...)> Equal{};

  template<auto... OtherValues>
    requires(sizeof...(Values) != sizeof...(OtherValues))
  static constexpr BoolConstant<false> Equal{};*/

  static constexpr size_t Size = sizeof...(Values);

  static constexpr BoolConstant<Size == 0> Empty {};

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

  template<template<auto...> typename Target>
  using Rebind = Target<Values...>;

  //! @TODO find a way that the user doesn't need to provide empty template arguments
  template<typename = void>
  static constexpr auto Front = FrontHelper<Values...>::value;
  template<typename = void>
  static constexpr auto Back = BackHelper<Values...>::value;

  using Unique = typename UniqueHelper<Values...>::type;

  template<template<auto> typename Predicate>
  using Filter = typename FilterHelper<Predicate, Values...>::type;

  using LeftShift  = typename LShiftHelper<Values...>::type;
  using RightShift = typename RShiftHelper<Values...>::type;

  template<size_t Count>
  using Take = typename TakeHelper<Count, Values...>::type;

  template<size_t Count>
  using Drop = typename DropHelper<Count, Values...>::type;

  using Reverse = typename ReverseHelper<Values...>::type;
};

} // namespace flp
