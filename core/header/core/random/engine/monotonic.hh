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

  template<typename RType>
  [[nodiscard]]
  RType get()
    requires (sizeof(RType) <= sizeof(Result)) {
    return static_cast<RType>((*this)() & mask<RType>());
  }

  template<typename RType>
  [[nodiscard]]
  RType get()
    requires (sizeof(RType) > sizeof(Result)) {
    RType value{};

    size_t b_counter{};
    for (;b_counter + sizeof(Result) <= sizeof(RType); b_counter += sizeof(Result)) {
      value <<= (sizeof(Result) * 8);
      value |= (*this)();
    }

    return value;
  }

  template<typename RType>
  constexpr
  static
  RType mask() {
    RType value{1};

    for (size_t i = 0; i < sizeof(RType) * 8; ++i) {
      value <<= 1;
      value |= 1;
    }

    return value;
  }

  Seed _seed{};
  Result state{};
};
static_assert(Engine<Monotonic>);

}
