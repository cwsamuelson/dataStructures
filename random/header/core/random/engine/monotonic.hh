#pragma once

#include <cstdint>
#include <cstddef>
#include <limits>

namespace flp::Random {

struct Monotonic {
  using Result = size_t;
  using Seed = size_t;

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
  Monotonic() noexcept = default;

  constexpr
  Monotonic(const Seed seed) noexcept
    : _seed(seed)
    , state(_seed)
  {}

  [[nodiscard]]
  constexpr
  Result operator()() noexcept {
    return state++;
  }

  [[nodiscard]]
  constexpr
  double entropy() const noexcept {
    return 0.;
  }

  [[nodiscard]]
  constexpr
  Seed seed() const noexcept {
    return _seed;
  }

  constexpr
  void seed(const Seed seed) noexcept {
    _seed = seed;
    state = _seed;
  }

  constexpr
  void discard() noexcept {
    discard(1);
  }

  constexpr
  void discard(size_t count) noexcept {
    while (count-- > 1) {
      [[maybe_unused]]const auto x = (*this)();
    }
  }

  Seed _seed{};
  Result state{};
};
static_assert(Engine<Monotonic>);

}
