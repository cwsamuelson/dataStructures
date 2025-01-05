#pragma once

#include <type_pack.hh>

#include <concepts>
#include <cstddef>
#include <type_traits>

namespace flp {

template<typename...>
class TypeSetImpl;

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

template<>
class TypeSetImpl<> {
public:
  using Pack = TypePack<>;

  template<typename...>
  friend class TypeSetImpl;

  template<typename... OtherArgs>
  constexpr bool operator==(const TypeSetImpl<OtherArgs...>&) const {
    return sizeof...(OtherArgs) == 0;
  }

  static constexpr auto Size = Pack::Size;

  static constexpr auto Empty = Pack::Empty;

  template<typename>
  static constexpr BoolConstant<false> Contains{};

  template<typename...Types>
  using Insert = TypePack<Types...>::Unique::template Rebind<TypeSetImpl>;

  template<typename>
  using Erase = TypeSetImpl<>;

  template<template<typename> typename Predicate>
  static constexpr BoolConstant<false> AnyOf{};
  template<template<typename> typename Predicate>
  static constexpr BoolConstant<false> AllOf{};

  template<template<typename> typename>
  using Transform = TypeSetImpl<>;

  template<template<typename...> typename Target>
  using Rebind = Target<>;

  template<template<typename> typename Predicate>
  using Filter = Pack::template Filter<Predicate>::template Rebind<TypeSetImpl>;

// Intersection
// Difference
// Symmetric Difference
// Union
};

template<typename T1, typename... Args>
class TypeSetImpl<T1, Args...> {
public:
  using Pack = TypePack<T1, Args...>;

  template<typename...>
  friend class TypeSetImpl;
            
  template<typename... OtherArgs>
  constexpr bool operator==(const TypeSetImpl<OtherArgs...>&) const {
    return (sizeof...(OtherArgs) == (sizeof...(Args) + 1)) and (Contains<OtherArgs> and ...)
       and (TypeSetImpl<OtherArgs...>::template Contains<T1> and (TypeSetImpl<OtherArgs...>::template Contains<Args> and ...));
  }

  static constexpr auto Size = Pack::Size;

  static constexpr auto Empty = Pack::Empty;

  template<typename Type>
  static constexpr BoolConstant<std::same_as<Type, T1> or (std::same_as<Type, Args> or ...)> Contains{};

  template<typename... Types>
  using Insert = TypePack<T1, Args..., Types...>::Unique::template Rebind<TypeSetImpl>;

  template<typename Type>
  using Erase = std::conditional_t<
    not Contains<Type>,
      TypeSetImpl<T1, Args...>,
      std::conditional_t<
        std::same_as<T1, Type>,
          typename TypeSetImpl<Args...>::Erase<Type>,
          typename TypeSetImpl<Args...>::Erase<Type>::Insert<T1>
        >
      >;

  template<template<typename> typename Predicate>
  static constexpr BoolConstant<(Predicate<T1>::value or (Predicate<Args>::value or ...))> AnyOf{};
  template<template<typename> typename Predicate>
  static constexpr BoolConstant<(Predicate<T1>::value and (Predicate<Args>::value and ...))> AllOf{};

  template<template<typename> typename Predicate>
  using Transform = typename Pack::Transform<Predicate>::Unique::template Rebind<TypeSetImpl>;

  template<template<typename...> typename Target>
  using Rebind = Target<T1, Args...>;

  template<template<typename> typename Predicate>
  using Filter = Pack::template Filter<Predicate>::template Rebind<TypeSetImpl>;

// Intersection
// Difference
// Symmetric Difference
// Union
};

// is this one needed?
template<typename Type>
class TypeSetImpl<Type> {
public:
  using Pack = TypePack<Type>;

  template<typename...>
  friend class TypeSetImpl;

  template<typename... OtherArgs>
  constexpr bool operator==(const TypeSetImpl<OtherArgs...>&) const {
    return (Contains<OtherArgs> and ...);
  }

  static constexpr auto Size = Pack::Size;

  static constexpr auto Empty = Pack::Empty;

  template<typename OtherType>
  static constexpr BoolConstant<std::same_as<OtherType, Type>> Contains{};

  template<typename... Types>
  using Insert = TypePack<Type, Types...>::Unique::template Rebind<TypeSetImpl>;

  template<typename OtherType>
  using Erase = std::conditional_t<
    std::same_as<OtherType, Type>,
      TypeSetImpl<>,
      TypeSetImpl<Type>
    >;

  template<template<typename> typename Predicate>
  static constexpr BoolConstant<Predicate<Type>::value> AnyOf{};
  template<template<typename> typename Predicate>
  static constexpr BoolConstant<Predicate<Type>::value> AllOf{};

  template<template<typename> typename Predicate>
  using Transform = typename Pack::Transform<Predicate>::Unique::template Rebind<TypeSetImpl>;

  template<template<typename...> typename Target>
  using Rebind = Target<Type>;

  template<template<typename> typename Predicate>
  using Filter = std::conditional_t<Predicate<Type>::value, TypeSetImpl<Type>, TypeSetImpl<>>;

// Intersection
// Difference
// Symmetric Difference
// Union
};

template<typename... Args>
struct TypeSet : TypePack<Args...>::Unique::template Rebind<TypeSetImpl> {};

} // namespace flp
