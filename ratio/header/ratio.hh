#pragma once

#include <cstdint>

namespace flp {

template<uint64_t Numerator, uint64_t Denominator>
struct RatioType {
  [[nodiscard]]
  constexpr operator double() const noexcept {
    return static_cast<double>(Numerator) / static_cast<double>(Denominator);
  }

  // lcm
  // + -
  // * /
};

struct RatioValue {
  uint64_t numerator{};
  uint64_t denominator{};

  [[nodiscard]]
  constexpr operator double() const noexcept {
    return static_cast<double>(numerator) / static_cast<double>(denominator);
  }

  /*[[nodiscard]]
  constexpr RatioValue operator+(const RatioValue& ratio) const noexcept {
  }*/

  // lcm
  // + -
  // * /
};

} // namespace flp

