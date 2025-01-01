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
  constexpr Self operator+(this const Self& self, const Other& other) const {
    return self.order + other.order;
  }

  template<typename Self, typename Other>
    requires std::same_as<Self, Other>
  [[nodiscard]]
  constexpr Self operator-(this const Self& self, const Other& other) const {
    return self.order - other.order;
  }
};

struct LengthBase : MeasureBase {};
struct TimeBase : MeasureBase {};
struct MassBase : MeasureBase {};
struct CurrentBase : MeasureBase {};
struct TemperatureBase : MeasureBase {};
struct CandelaBase : MeasureBase {};
struct MoneyBase : MeasureBase {};
struct AngleBase : MeasureBase {};
struct PercentageBase : MeasureBase {};
struct CountBase : MeasureBase {};
struct ByteBase : MeasureBase {};
struct TickBase : MeasureBase {};

template<auto... Measures>
  requires(std::derived_from<decltype(Measures), MeasureBase> && ...)
      and ((not std::same_as<decltype(Measures), MeasureBase>) && ...)
struct Measure {
  static constexpr typename Rebind<TypeSet<decltype(Measures)...>, std::tuple>::type measures;

  template<auto... OtherMeasures>
  constexpr auto operator*(const Measure<OtherMeasures...>& other) {
    auto f = []<typename Measure, typename Tuple>(const Measure& measure, const Tuple& tuple) {
      if constexpr (typename Rebind<Tuple, TypeSet>::type::template contains<Measure>()) {
        return measure + std::get<Measure>(tuple);
      } else {
        return  measure;
      }
    };
    (f(std::get<Measures>(measures), other), ...);
  }
};

} // namespace flp
