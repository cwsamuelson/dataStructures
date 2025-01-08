#pragma once

#include <measure_pack.hh>
#include <value_pack.hh>

#include <core/concepts.hh>

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

namespace {

template<auto... Measures>
struct MeasureImpl {
  template<auto... OtherMeasures>
  constexpr auto operator*(const MeasureImpl<OtherMeasures...>& other) {
    constexpr auto f = []<typename Meas>(const Meas& measure, const MeasureImpl<OtherMeasures...>&) {
      if constexpr (MeasurePack<OtherMeasures...>::template Has<Meas>) {
        return measure + MeasurePack<OtherMeasures...>::template Select<Meas>::Front;
      } else {
        return measure;
      }
    }

    return MeasureImpl<f(Measures, other)...> {};
  }
};

}

// must derive from, but not be `MeasureBase`
template<auto... Measures>
  requires(std::derived_from<decltype(Measures), MeasureBase> && ...)
      and ((not std::same_as<decltype(Measures), MeasureBase>) && ...)
struct Measure : MeasurePack<Measures...>::UniqueTypes::template Rebind<MeasureImpl> {};

} // namespace flp

