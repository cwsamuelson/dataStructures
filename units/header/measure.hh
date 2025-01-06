#pragma once

#include <core/concepts.hh>
//#include <type_set.hh>

#include <concepts>
#include <cstddef>
#include <tuple>

namespace flp {

template<auto...>
class MeasureSet;

template<>
class MeasureSet<> {
public:
  template<auto...>
  friend class MeasureSet;

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
    return typename RebindValues<typename UniqueValues<Values...>::type, MeasureSet>::type {};
  }

  template<auto>
  static constexpr auto erase() {
    return MeasureSet {};
  }

  template<auto... OtherArgs>
  constexpr bool operator==(const MeasureSet<OtherArgs...>&) const {
    return sizeof...(OtherArgs) == 0;
  }

  // intersection
  // difference
  // symmetric difference
  // union

  template<auto... OtherArgs>
  static constexpr auto union_() {
    return MeasureSet<OtherArgs...> {};
  }

  template<auto... OtherArgs>
  static constexpr auto intersection() {}
};

template<auto T1, auto... Args>
class MeasureSet<T1, Args...> {
public:
  template<auto...>
  friend class MeasureSet;

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
    return typename RebindValues<typename UniqueValues<T1, Args..., Values...>::type, MeasureSet>::type {};
  }

  template<auto Value>
  static constexpr auto erase() {
    if constexpr (not contains<Value>()) {
      return MeasureSet {};
    } else if constexpr (std::same_as<T1, Value>) {
      return typename RebindValues<typename UniqueValues<Args...>::type, MeasureSet>::type {};
    } else {
      return typename RebindValues<typename UniqueValues<Args...>::type, MeasureSet>::type {}
        .template erase<Value>()
        .template insert<T1>();
    }
  }

  template<auto... OtherArgs>
  constexpr bool operator==(const MeasureSet<OtherArgs...>& other) const {
    return (sizeof...(OtherArgs) == (sizeof...(Args) + 1)) and (contains<OtherArgs>() and ...)
       and (other.template contains<T1>() and (other.template contains<Args>() and ...));
  }
};

template<auto Value>
class MeasureSet<Value> {
public:
  template<auto...>
  friend class MeasureSet;

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
    return typename RebindValues<typename UniqueValues<Value, Values...>::type, MeasureSet>::type {};
  }

  template<auto OtherValue>
  static constexpr auto erase() {
    if constexpr (std::same_as<OtherValue, Value>) {
      return MeasureSet<> {};
    } else {
      return MeasureSet {};
    }
  }

  template<auto... OtherArgs>
  constexpr bool operator==(const MeasureSet<OtherArgs...>&) const {
    return (contains<OtherArgs>() and ...);
  }
};

template<auto... Args>
struct ValueSet : RebindValues<typename UniqueValues<Args...>::type, MeasureSet>::type {};



struct MeasureBase {
  size_t order;

  template<typename Self, typename Other>
    requires std::same_as<Self, Other>
  [[nodiscard]]
  constexpr Self operator+(this const Self& self, const Other& other) {
    return self.order + other.order;
  }

  template<typename Self, typename Other>
    requires std::same_as<Self, Other>
  [[nodiscard]]
  constexpr Self operator-(this const Self& self, const Other& other) {
    return self.order - other.order;
  }
};

// must derive from, but not be `MeasureBase`
template<auto... Measures>
  requires(std::derived_from<decltype(Measures), MeasureBase> && ...)
      and ((not std::same_as<decltype(Measures), MeasureBase>) && ...)
struct Measure {
  static constexpr typename RebindTypes<TypeSet<decltype(Measures)...>, std::tuple>::type measures {};

  template<auto... OtherMeasures>
  constexpr auto operator*(const Measure<OtherMeasures...>& other) {
    constexpr auto f = []<typename Meas, typename Tuple>(const Meas& measure, const Tuple& tuple) {
      if constexpr (typename RebindTypes<Tuple, TypeSet>::type::template contains<Meas>()) {
        return measure + std::get<Meas>(tuple);
      } else {
        return measure;
      }
    };
    return Measure<f(std::get<Measures>(measures), other)...> {};
  }
};

} // namespace flp
