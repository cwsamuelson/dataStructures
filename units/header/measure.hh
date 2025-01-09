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

  template<typename Self, std::derived_from<MeasureBase> Other>
  [[nodiscard]]
  constexpr auto operator==(this const Self&, const Other&) noexcept {
    return false;
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

  template<typename Self>
  [[nodiscard]]
  constexpr Self operator-(this const Self& self) noexcept {
    return {-self.order};
  }
};

template<auto... Measures>
  requires(std::derived_from<decltype(Measures), MeasureBase> && ...)
      and ((not std::same_as<decltype(Measures), MeasureBase>) && ...)
struct Measure;

namespace {

template<auto... Measures>
struct MeasureImpl {
  template<auto ...OtherMeasures>
    requires (sizeof...(Measures) == sizeof...(OtherMeasures))
  [[nodiscard]]
  constexpr friend bool operator==(const MeasureImpl& lhs, const MeasureImpl<OtherMeasures...>& rhs) noexcept {
    return ValuePack<Measures...>{} == ValuePack<OtherMeasures...>{};
  }

  template<auto ...OtherMeasures>
    requires (sizeof...(Measures) != sizeof...(OtherMeasures))
  [[nodiscard]]
  constexpr friend bool operator==(const MeasureImpl& lhs, const MeasureImpl<OtherMeasures...>& rhs) noexcept {
    return false;
  }

  template<auto... OtherMeasures>
  constexpr auto operator*(const MeasureImpl<OtherMeasures...>& other) noexcept {
    constexpr auto f = []<typename Meas>(const Meas& measure, const MeasureImpl<OtherMeasures...>&) {
      if constexpr (MeasurePack<OtherMeasures...>::template Has<Meas>) {
        return Meas{measure + MeasurePack<OtherMeasures...>::template Select<Meas>};
      } else {
        return measure;
      }
    };

    constexpr auto g = []<typename Meas>(const Meas& measure, const MeasureImpl<Measures...>&) {
      if constexpr (MeasurePack<Measures...>::template Has<Meas>) {
        return Meas{0};
      } else {
        return measure;
      }
    };

    return Measure<g(OtherMeasures, *this)..., f(Measures, other)...> {};
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

    constexpr auto g = []<typename Meas>(const Meas& measure, const MeasureImpl<Measures...>&) {
      if constexpr (MeasurePack<Measures...>::template Has<Meas>) {
        return Meas{0};
      } else {
        return -measure;
      }
    };

    return Measure<g(OtherMeasures, *this)..., f(Measures, other)...> {};
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
struct Measure : MeasurePack<Measures...>::UniqueTypes::Filter<EmptyFilter>::template Rebind<MeasureImpl>{};

} // namespace flp

