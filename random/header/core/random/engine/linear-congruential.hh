#pragma once

#include <cstddef>
#include <cstdint>
#include <limits>

// https://en.cppreference.com/w/cpp/numeric/random/linear_congruential_engine.html
// https://en.wikipedia.org/wiki/Linear_congruential_generator

namespace flp::Random {

template<typename Type = uint_fast64_t, size_t Multiplier = 48271, size_t Increment = 0, size_t Modulus = 2147483647>
struct LinearCongruential {
  using Result = Type;
  using Seed = Type;

  [[nodiscard]]
  static
  constexpr
  Result min() noexcept {
    return std::numeric_limits<Type>::min();
  }

  [[nodiscard]]
  static
  constexpr
  Result max() noexcept {
    return std::numeric_limits<Type>::max();
  }

  constexpr
  LinearCongruential() noexcept
    : LinearCongruential(0)
  {}

  constexpr
  LinearCongruential(const Seed seed) noexcept
    : _seed(seed) {
    if (Increment % Modulus == 0 and seed % Modulus == 0) {
      state = 1;
    } else {
      state = seed % Modulus;
    }
  }

  [[nodiscard]]
  constexpr
  Result operator()() noexcept {
    state = ((Multiplier * state) + Increment) % Modulus;
    return state;
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
static_assert(Engine<LinearCongruential<>>);

}
