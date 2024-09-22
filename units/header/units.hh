#pragma once

#include <measure.hh>
#include <system.hh>

#include <catch2/internal/catch_clara.hpp>

namespace flp {

//! @TODO conditional noexcept
template<typename Type, Measure measure, System system>
struct Unit {
  Type value {};

  constexpr          Unit() = default;
  constexpr explicit Unit(const Type value)
    : value(value) {}

  constexpr Unit(const Unit&)     = default;
  constexpr Unit(Unit&&) noexcept = default;

  constexpr Unit& operator=(const Unit&)     = default;
  constexpr Unit& operator=(Unit&&) noexcept = default;

  ~Unit() = default;

  friend auto operator<=>(const Unit&, const Unit&) noexcept = default;

  template<typename OtherType, System OtherSystem>
  [[nodiscard]] constexpr explicit Unit(const Unit<OtherType, measure, OtherSystem>& other) {}

  [[nodiscard]]
  explicit
  operator Type() const {
    return value;
  }

  template<typename OtherType, System OtherSystem>
  [[nodiscard]]
  explicit
  operator Unit<OtherType, measure, OtherSystem>() const {
    return value;
  }

  [[nodiscard]]
  friend Unit
  operator+(const Unit& lhs, const Unit& rhs) {
    return Unit(lhs.value + rhs.value);
  }

  [[nodiscard]]
  friend Unit
  operator-(const Unit& lhs, const Unit& rhs) {
    return Unit(lhs.value - rhs.value);
  }

  template<typename LType, typename RType, Measure LMeasure, Measure RMeasure, System LSystem, System RSystem>
  [[nodiscard]]
  friend auto
  operator*(const Unit& lhs, const Unit& rhs) {
    using Result_t = Unit<std::common_type_t<LType, RType>, LMeasure * RMeasure, ResultSystem>;
    return { rhs.value * lhs.value };
  }

  template<typename LType, typename RType, Measure LMeasure, Measure RMeasure, System LSystem, System RSystem>
  [[nodiscard]]
  friend auto
  operator/(const Unit& lhs, const Unit& rhs) {
    using Result_t = Unit<std::common_type_t<LType, RType>, LMeasure / RMeasure, ResultSystem>;
    return { rhs.value / lhs.value };
  }
};

template<System system1, System system2>
// generic case: convert to SI, and then to requested system
struct Converter {
  constexpr auto operator()(Unit value) {}
};

template<System system>
struct Converter<system, system> {
  constexpr auto operator()(Unit value) {
    return value;
  }
};

} // namespace flp
