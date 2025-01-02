#pragma once

#include <type_set.hh>

#include <concepts>
#include <cstddef>
#include <tuple>

namespace flp {

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
  static constexpr typename Rebind<TypeSet<decltype(Measures)...>, std::tuple>::type measures {};

  template<auto... OtherMeasures>
  constexpr auto operator*(const Measure<OtherMeasures...>& other) {
    constexpr auto f = []<typename Measure, typename Tuple>(const Measure& measure, const Tuple& tuple) {
      if constexpr (typename Rebind<Tuple, TypeSet>::type::template contains<Measure>()) {
        return measure + std::get<Measure>(tuple);
      } else {
        return measure;
      }
    };
    return Measure<f(std::get<Measures>(measures), other)...> {};
  }
};

} // namespace flp
