#pragma once

#include <concepts>
#include <cstddef>
#include <tuple>
#include <type_traits>

namespace flp {

template<typename...>
struct Prepend;

template<typename T1, typename... Args>
struct Prepend<T1, std::tuple<Args...>> {
  using type = std::tuple<T1, Args...>;
};

template<typename...>
struct UniqueTypes;

template<typename T1, typename... Args>
struct UniqueTypes<T1, Args...> {
  template<typename T, typename... Ts>
  static constexpr bool contains = (std::same_as<T, Ts> or ...);

  using type = std::conditional_t<contains<T1, Args...>,
                                  typename UniqueTypes<Args...>::type,
                                  typename Prepend<T1, typename UniqueTypes<Args...>::type>::type>;
};

template<>
struct UniqueTypes<> {
  using type = std::tuple<>;
};

template<typename, template<typename...> typename, typename...>
struct Rebind;

template<template<typename...> typename Source, template<typename...> typename Target, typename... Args>
struct Rebind<Source<Args...>, Target> {
  using type = Target<Args...>;
};

template<typename...>
class TypeSet;

template<>
class TypeSet<> {
public:
  constexpr TypeSet() = default;

  constexpr TypeSet(const TypeSet&) = default;
  constexpr TypeSet(TypeSet&&)      = default;

  constexpr ~TypeSet() = default;

  constexpr TypeSet& operator=(const TypeSet&) = delete;
  constexpr TypeSet& operator=(TypeSet&&)      = delete;

  template<typename...>
  friend class TypeSet;

  static constexpr size_t size() {
    return 0;
  }

  static constexpr bool empty() {
    return true;
  }

  template<typename>
  static constexpr bool contains() {
    return false;
  }

  template<typename... Types>
  static constexpr auto insert() {
    return typename Rebind<typename UniqueTypes<Types...>::type, TypeSet>::type {};
  }

  template<typename>
  static constexpr auto erase() {
    return TypeSet {};
  }

  template<typename... OtherArgs>
  constexpr bool operator==(const TypeSet<OtherArgs...>&) const {
    return sizeof...(OtherArgs) == 0;
  }
};

template<typename T1, typename... Args>
class TypeSet<T1, Args...> {
public:
  constexpr TypeSet() = default;

  constexpr TypeSet(const TypeSet&) = default;
  constexpr TypeSet(TypeSet&&)      = default;

  constexpr ~TypeSet() = default;

  constexpr TypeSet& operator=(const TypeSet&) = delete;
  constexpr TypeSet& operator=(TypeSet&&)      = delete;

  template<typename...>
  friend class TypeSet;

  static constexpr size_t size() {
    return (sizeof...(Args)) + 1;
  }

  static constexpr bool empty() {
    return false;
  }

  template<typename Type>
  static constexpr bool contains() {
    return std::same_as<Type, T1> or (std::same_as<Type, Args> or ...);
  }

  template<typename... Types>
  static constexpr auto insert() {
    return typename Rebind<typename UniqueTypes<T1, Args..., Types...>::type, TypeSet>::type {};
  }

  template<typename Type>
  static constexpr auto erase() {
    if constexpr (not contains<Type>()) {
      return TypeSet {};
    } else if constexpr (std::same_as<T1, Type>) {
      return typename Rebind<typename UniqueTypes<Args...>::type, TypeSet>::type {};
    } else {
      return typename Rebind<typename UniqueTypes<Args...>::type, TypeSet>::type {}
        .template erase<Type>()
        .template insert<T1>();
    }
  }

  template<typename... OtherArgs>
  constexpr bool operator==(const TypeSet<OtherArgs...>& other) const {
    return (sizeof...(OtherArgs) == (sizeof...(Args) + 1)) and (contains<OtherArgs>() and ...)
       and (other.template contains<T1>() and (other.template contains<Args>() and ...));
  }
};

template<typename Type>
class TypeSet<Type> {
public:
  constexpr TypeSet() = default;

  constexpr TypeSet(const TypeSet&) = default;
  constexpr TypeSet(TypeSet&&)      = default;

  constexpr ~TypeSet() = default;

  constexpr TypeSet& operator=(const TypeSet&) = delete;
  constexpr TypeSet& operator=(TypeSet&&)      = delete;

  template<typename...>
  friend class TypeSet;

  static constexpr size_t size() {
    return 1;
  }

  static constexpr bool empty() {
    return false;
  }

  template<typename OtherType>
  static constexpr bool contains() {
    return std::same_as<OtherType, Type>;
  }

  template<typename... Types>
  static constexpr auto insert() {
    return typename Rebind<typename UniqueTypes<Type, Types...>::type, TypeSet>::type {};
  }

  template<typename OtherType>
  static constexpr auto erase() {
    if constexpr (std::same_as<OtherType, Type>) {
      return TypeSet<> {};
    } else {
      return TypeSet {};
    }
  }

  template<typename... OtherArgs>
  constexpr bool operator==(const TypeSet<OtherArgs...>&) const {
    return (contains<OtherArgs>() and ...);
  }
};

} // namespace flp
