#pragma once

#include <cstdint>
#include <cstddef>
#include <limits>

namespace flp::Random {

struct Monotonic {
  using Result = size_t;

  static
  constexpr
  Result min() noexcept {
    return std::numeric_limits<Result>::min();
  }

  static
  constexpr
  Result max() noexcept {
    return std::numeric_limits<Result>::max();
  }

  constexpr
  Monotonic() = default;

  constexpr
  Monotonic(const Result seed)
    : state(seed)
  {}

  [[nodiscard]]
  constexpr
  Result operator()() {
    return state++;
  }

  [[nodiscard]]
  constexpr
  double entropy() const noexcept {
    return 0.;
  }

  Result state{};
};

}
