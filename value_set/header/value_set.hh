#pragma once

#include <concepts>
#include <cstddef>
#include <tuple>
#include <type_traits>

namespace flp {

namespace {

template<auto...>
struct PrependValue;

template<auto T1, auto... Args>
struct PrependValue<T1, std::tuple<Args...>> {
  using type = std::tuple<T1, Args...>;
};

template<auto...>
struct UniqueValues;

template<auto T1, auto... Args>
struct UniqueValues<T1, Args...> {
  template<auto T, auto... Ts>
  static constexpr bool contains = (std::same_as<T, Ts> or ...);

  using type = std::conditional_t<contains<T1, Args...>,
                                  typename UniqueValues<Args...>::type,
                                  typename PrependValue<T1, typename UniqueValues<Args...>::type>::type>;
};

template<>
struct UniqueValues<> {
  using type = std::tuple<>;
};

template<template<auto...> typename, auto...>
struct RebindValues;

template<template<auto...> typename Source, template<auto...> typename Target, auto... Args>
struct RebindValues<Source<Args...>, Target> {
  using type = Target<Args...>;
};

}

template<auto...>
class ValueSetImpl;

template<>
class ValueSetImpl<> {
public:
  constexpr ValueSetImpl() = default;

  constexpr ValueSetImpl(const ValueSetImpl&) = default;
  constexpr ValueSetImpl(ValueSetImpl&&)      = default;

  constexpr ~ValueSetImpl() = default;

  constexpr ValueSetImpl& operator=(const ValueSetImpl&) = delete;
  constexpr ValueSetImpl& operator=(ValueSetImpl&&)      = delete;

  template<auto...>
  friend class ValueSetImpl;

  static constexpr size_t size() {
    return 0;
  }

  static constexpr bool empty() {
    return true;
  }

  template<auto>
  static constexpr bool contains() {
    return false;
  }

  template<auto... Values>
  static constexpr auto insert() {
    return typename RebindValues<typename UniqueValues<Values...>::type, ValueSetImpl>::type {};
  }

  template<auto>
  static constexpr auto erase() {
    return ValueSetImpl {};
  }

  template<auto... OtherArgs>
  constexpr bool operator==(const ValueSetImpl<OtherArgs...>&) const {
    return sizeof...(OtherArgs) == 0;
  }

  // intersection
  // difference
  // symmetric difference
  // union

  template<auto... OtherArgs>
  static constexpr auto union_() {
    return ValueSetImpl<OtherArgs...> {};
  }

  template<auto... OtherArgs>
  static constexpr auto intersection() {}
};

template<auto T1, auto... Args>
class ValueSetImpl<T1, Args...> {
public:
  constexpr ValueSetImpl() = default;

  constexpr ValueSetImpl(const ValueSetImpl&) = default;
  constexpr ValueSetImpl(ValueSetImpl&&)      = default;

  constexpr ~ValueSetImpl() = default;

  constexpr ValueSetImpl& operator=(const ValueSetImpl&) = delete;
  constexpr ValueSetImpl& operator=(ValueSetImpl&&)      = delete;

  template<auto...>
  friend class ValueSetImpl;

  static constexpr size_t size() {
    return (sizeof...(Args)) + 1;
  }

  static constexpr bool empty() {
    return false;
  }

  template<auto Value>
  static constexpr bool contains() {
    return std::same_as<Value, T1> or (std::same_as<Value, Args> or ...);
  }

  template<auto... Values>
  static constexpr auto insert() {
    return typename RebindValues<typename UniqueValues<T1, Args..., Values...>::type, ValueSetImpl>::type {};
  }

  template<auto Value>
  static constexpr auto erase() {
    if constexpr (not contains<Value>()) {
      return ValueSetImpl {};
    } else if constexpr (std::same_as<T1, Value>) {
      return typename RebindValues<typename UniqueValues<Args...>::type, ValueSetImpl>::type {};
    } else {
      return typename RebindValues<typename UniqueValues<Args...>::type, ValueSetImpl>::type {}
        .template erase<Value>()
        .template insert<T1>();
    }
  }

  template<auto... OtherArgs>
  constexpr bool operator==(const ValueSetImpl<OtherArgs...>& other) const {
    return (sizeof...(OtherArgs) == (sizeof...(Args) + 1)) and (contains<OtherArgs>() and ...)
       and (other.template contains<T1>() and (other.template contains<Args>() and ...));
  }
};

template<auto Value>
class ValueSetImpl<Value> {
public:
  constexpr ValueSetImpl() = default;

  constexpr ValueSetImpl(const ValueSetImpl&) = default;
  constexpr ValueSetImpl(ValueSetImpl&&)      = default;

  constexpr ~ValueSetImpl() = default;

  constexpr ValueSetImpl& operator=(const ValueSetImpl&) = delete;
  constexpr ValueSetImpl& operator=(ValueSetImpl&&)      = delete;

  template<auto...>
  friend class ValueSetImpl;

  static constexpr size_t size() {
    return 1;
  }

  static constexpr bool empty() {
    return false;
  }

  template<auto OtherValue>
  static constexpr bool contains() {
    return std::same_as<OtherValue, Value>;
  }

  template<auto... Values>
  static constexpr auto insert() {
    return typename RebindValues<typename UniqueValues<Value, Values...>::type, ValueSetImpl>::type {};
  }

  template<auto OtherValue>
  static constexpr auto erase() {
    if constexpr (std::same_as<OtherValue, Value>) {
      return ValueSetImpl<> {};
    } else {
      return ValueSetImpl {};
    }
  }

  template<auto... OtherArgs>
  constexpr bool operator==(const ValueSetImpl<OtherArgs...>&) const {
    return (contains<OtherArgs>() and ...);
  }
};

template<auto... Args>
struct ValueSet : RebindValues<typename UniqueValues<Args...>::type, ValueSetImpl>::type {};

} // namespace flp
