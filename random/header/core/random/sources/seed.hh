#pragma once

#include <cstddef>
#include <limits>

namespace flp::Random {

struct Seed {
  using Seed_t = size_t;
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

  Seed();
  Seed(Seed_t seed);

  Result operator()();

  [[nodiscard]]
  double entropy() const noexcept;
};

} // namespace flp
