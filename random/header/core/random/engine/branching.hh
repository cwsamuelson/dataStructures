#pragma once

namespace flp::Random {

template<typename Engine>
struct Branching {
  using Result = size_t;

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
  Branching(Engine&& engine)
    : base_engine(std::forward<Engine>(engine))
  {}

  constexpr
  Branching(const Result seed)
    : base_engine(seed)
  {}

  [[nodiscard]]
  constexpr
  Result operator()() {
    return base_engine();
  }

  [[nodiscard]]
  constexpr
  void seed(const Seed seed) const {
    base_engine.seed(seed);
  }

  constexpr
  void discard() {
    base_engine.discard(1);
  }

  constexpr
  void discard(const size_t count) {
    base_engine.discard(count);
  }

  constexpr
  Branching fork() {
    return {(*this)()};
  }

  Engine base_engine;
};

}
