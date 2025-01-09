#pragma once

#include <measure_pack.hh>
#include <value_pack.hh>

#include <core/concepts.hh>

#include <concepts>
#include <cstddef>
#include <tuple>

namespace flp {

struct MeasureBase {
  signed long long int order;

  template<typename Self>
  [[nodiscard]]
  constexpr auto operator<=>(this const Self& self, const Self& other) noexcept {
    return self.order <=> other.order;
  }

  template<typename Self>
  [[nodiscard]]
  constexpr auto operator==(this const Self& self, const Self& other) noexcept {
    return self.order == other.order;
  }

  template<typename Self>
  [[nodiscard]]
  constexpr Self operator+(this const Self& self, const Self& other) noexcept {
    return {self.order + other.order};
  }

  template<typename Self>
  [[nodiscard]]
  constexpr Self operator-(this const Self& self, const Self& other) noexcept {
    return {self.order - other.order};
  }
};

template<auto... Measures>
  requires(std::derived_from<decltype(Measures), MeasureBase> && ...)
      and ((not std::same_as<decltype(Measures), MeasureBase>) && ...)
struct Measure;

namespace {

template<auto... Measures>
struct MeasureImpl {
  template<auto... OtherMeasures>
  constexpr auto operator*(const MeasureImpl<OtherMeasures...>& other) noexcept {
    constexpr auto f = []<typename Meas>(const Meas& measure, const MeasureImpl<OtherMeasures...>&) {
      if constexpr (MeasurePack<OtherMeasures...>::template Has<Meas>) {
        return Meas{measure + MeasurePack<OtherMeasures...>::template Select<Meas>};
      } else {
        return measure;
      }
    };

    return Measure<f(Measures, other)...> {};
  }

  template<auto... OtherMeasures>
  constexpr auto operator/(const MeasureImpl<OtherMeasures...>& other) noexcept {
    constexpr auto f = []<typename Meas>(const Meas& measure, const MeasureImpl<OtherMeasures...>&) {
      if constexpr (MeasurePack<OtherMeasures...>::template Has<Meas>) {
        return Meas{measure - MeasurePack<OtherMeasures...>::template Select<Meas>};
      } else {
        return measure;
      }
    };

    return Measure<f(Measures, other)...> {};
  }
};

template<auto Value>
struct EmptyFilter {
  static constexpr auto value = Value.order != 0;
};

}

// must derive from, but not be `MeasureBase`
template<auto... Measures>
  requires(std::derived_from<decltype(Measures), MeasureBase> && ...)
      and ((not std::same_as<decltype(Measures), MeasureBase>) && ...)
struct Measure : MeasurePack<Measures...>::UniqueTypes::Filter<EmptyFilter> ::template Rebind<MeasureImpl>{};

} // namespace flp

