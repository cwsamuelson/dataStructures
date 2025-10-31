#pragma once

#include <cstddef>
#include <limits>

namespace flp::Random {

struct Seed {
  using Seed = size_t;
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

  RandomSource();
  RandomSource(Seed seed);

  Result operator()();

  [[nodiscard]]
  double entropy() const noexcept;
};

} // namespace flp
