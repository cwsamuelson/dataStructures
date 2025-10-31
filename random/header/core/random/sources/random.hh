#pragma once

#include <limits>

namespace flp::Random {

// BAD name
struct Random {
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

  [[nodiscard]]
  Result operator()();
};

}
