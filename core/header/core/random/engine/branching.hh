#pragma once

#include "core/random/random.hh"

#include <limits>
#include <utility>

namespace flp::Random {

template<typename Engine_t>
struct Branching {
  // static_assert(Engine<Branching<Engine_t>>);

  using Result = Engine_t::Result;
  using Seed = Engine_t::Seed;

  [[nodiscard]]
  static
  constexpr
  Result min() noexcept {
    return std::numeric_limits<Result>::min();
  }

  [[nodiscard]]
  static
  constexpr
  Result max() noexcept {
    return std::numeric_limits<Result>::max();
  }

  template<typename ...Args>
  constexpr
  Branching(Args&& ...args)
    : base_engine(std::forward<Args>(args)...)
  {}

  constexpr
  Branching(Engine_t&& engine) noexcept
    : base_engine(std::forward<Engine_t>(engine))
  {}

  constexpr
  Branching(const Result seed) noexcept
    : base_engine(seed)
  {}

  [[nodiscard]]
  constexpr
  Result operator()() noexcept {
    return base_engine();
  }

  constexpr
  void seed(const Seed seed) const noexcept {
    base_engine.seed(seed);
  }

  [[nodiscard]]
  constexpr
  Seed seed() const noexcept {
    return base_engine.seed();
  }

  constexpr
  void discard() noexcept {
    base_engine.discard(1);
  }

  constexpr
  void discard(const size_t count) noexcept {
    base_engine.discard(count);
  }

  [[nodiscard]]
  constexpr
  Branching fork() const noexcept {
    return {(*this)()};
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

  Engine_t base_engine;
};

}
