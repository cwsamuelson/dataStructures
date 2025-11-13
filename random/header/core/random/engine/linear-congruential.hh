#pragma once

#include <limits>

// https://en.cppreference.com/w/cpp/numeric/random/linear_congruential_engine.html
// https://en.wikipedia.org/wiki/Linear_congruential_generator

namespace flp::Random {

size_t relation(const size_t seed, const size_t multiplier, const size_t increment, const size_t modulus) {
  return ((multiplier * seed) + increment) % modulus;
}

size_t relation(const size_t seed) {
  return relation(seed, 0, 0, 0);
}

template<typename Type, size_t Multiplier, size_t Increment, size_t Modulus>
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

  LinearCongruential(const Seed seed)
    : state(seed)
  {}

  [[nodiscard]]
  Result operator()() {
    const auto new_value = ((Multiplier * state) + Increment) % Modulus;
    state = new_value;
    return new_value;
  }

  [[nodiscard]]
  void seed(const Seed seed) const {
    state = seed;
  }

  void discard() {
    discard(1);
  }

  void discard(size_t count) {
    while (--count >= 0) {
      [[maybe_unused]](*this)();
    }
  }

  Seed state{};
};

}
