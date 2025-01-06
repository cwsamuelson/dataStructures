#pragma once

#include <value_pack.hh>

#include <core/traits.hh>

#include <concepts>
#include <cstddef>
#include <type_traits>

namespace flp {

// Equality
// Size
// Empty
// Contains
// Insert
// Erase
// AnyOf
// AllOf
// Transform
// Rebind
// Filter
// Intersection
// Difference
// Symmetric Difference
// Union

template<auto...>
class ValueSetImpl;

template<>
class ValueSetImpl<> {
public:
  using Pack = ValuePack<>;

  template<auto...>
  friend class ValueSetImpl;

  template<auto... OtherArgs>
  constexpr bool operator==(const ValueSetImpl<OtherArgs...>&) const {
    return sizeof...(OtherArgs) == 0;
  }

  static constexpr auto Size = Pack::Size;

  static constexpr auto Empty = Pack::Empty;

  template<auto>
  static constexpr BoolConstant<false> Contains {};

  template<auto... Values>
  using Insert = typename ValuePack<Values...>::Unique::template Rebind<ValueSetImpl>;

  template<auto>
  using Erase = ValueSetImpl<>;

  template<template<auto> typename Predicate>
  static constexpr BoolConstant<false> AnyOf {};
  template<template<auto> typename Predicate>
  static constexpr BoolConstant<false> AllOf {};

  template<template<auto> typename>
  using Transform = ValueSetImpl<>;

  template<template<auto...> typename Target>
  using Rebind = Target<>;

  template<template<auto> typename Predicate>
  using Filter = typename Pack::Filter<Predicate>::template Rebind<ValueSetImpl>;

  // Intersection
  // Difference
  // Symmetric Difference
  // Union
};

template<auto V1, auto... Values>
class ValueSetImpl<V1, Values...> {
public:
  using Pack = ValuePack<V1, Values...>;

  template<auto...>
  friend class ValueSetImpl;

  template<auto... OtherValues>
  constexpr bool operator==(const ValueSetImpl<OtherValues...>&) const {
    return (sizeof...(OtherValues) == (sizeof...(Values) + 1)) and (Contains<OtherValues> and ...)
       and (ValueSetImpl<OtherValues...>::template Contains<V1>
            and (ValueSetImpl<OtherValues...>::template Contains<Values> and ...));
  }

  static constexpr auto Size = Pack::Size;

  static constexpr auto Empty = Pack::Empty;

  template<auto Value>
  static constexpr BoolConstant<(Value == V1) or ((Value == Values) or ...)> Contains {};

  template<auto... OtherValues>
  using Insert = typename ValuePack<V1, Values..., OtherValues...>::Unique::template Rebind<ValueSetImpl>;

  template<auto Value>
  using Erase = std::conditional_t<not Contains<Value>,
                                   ValueSetImpl<V1, Values...>,
                                   std::conditional_t<(V1 == Value),
                                                      typename ValueSetImpl<Values...>::Erase<Value>,
                                                      typename ValueSetImpl<Values...>::Erase<Value>::Insert<V1>>>;

  template<template<auto> typename Predicate>
  static constexpr BoolConstant<(Predicate<V1>::value or (Predicate<Values>::value or ...))> AnyOf {};
  template<template<auto> typename Predicate>
  static constexpr BoolConstant<(Predicate<V1>::value and (Predicate<Values>::value and ...))> AllOf {};

  template<template<auto> typename Predicate>
  using Transform = typename Pack::template Transform<Predicate>::Unique::template Rebind<ValueSetImpl>;

  template<template<auto...> typename Target>
  using Rebind = Target<V1, Values...>;

  template<template<auto> typename Predicate>
  using Filter = typename Pack::template Filter<Predicate>::template Rebind<ValueSetImpl>;

  // Intersection
  // Difference
  // Symmetric Difference
  // Union
};

template<auto Value>
class ValueSetImpl<Value> {
public:
  using Pack = ValuePack<Value>;

  template<auto...>
  friend class ValueSetImpl;

  template<auto... OtherArgs>
  constexpr bool operator==(const ValueSetImpl<OtherArgs...>&) const {
    return (Contains<OtherArgs> and ...);
  }

  static constexpr auto Size = Pack::Size;

  static constexpr auto Empty = Pack::Empty;

  template<auto OtherValue>
  static constexpr BoolConstant<OtherValue == Value> Contains {};

  template<auto... OtherValues>
  using Insert = typename ValuePack<Value, OtherValues...>::Unique::template Rebind<ValueSetImpl>;

  template<auto OtherValue>
  using Erase = std::conditional_t<OtherValue == Value, ValueSetImpl<>, ValueSetImpl<Value>>;

  template<template<auto> typename Predicate>
  static constexpr BoolConstant<Predicate<Value>::value> AnyOf {};
  template<template<auto> typename Predicate>
  static constexpr BoolConstant<Predicate<Value>::value> AllOf {};

  template<template<auto> typename Predicate>
  using Transform = typename Pack::template Transform<Predicate>::Unique::template Rebind<ValueSetImpl>;

  template<template<auto...> typename Target>
  using Rebind = Target<Value>;

  template<template<auto> typename Predicate>
  using Filter = std::conditional_t<Predicate<Value>::value, ValueSetImpl<Value>, ValueSetImpl<>>;

  // Intersection
  // Difference
  // Symmetric Difference
  // Union
};

template<auto... Args>
struct ValueSet : ValuePack<Args...>::Unique::template Rebind<ValueSetImpl> {};

} // namespace flp
