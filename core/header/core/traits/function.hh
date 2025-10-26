#pragma once

namespace flp {

// These predicates are operating on values
// I'd like to have a set of them that operate on types

template<auto Value>
struct Identity {
  static constexpr auto value = Value;

  [[nodiscard]]
  constexpr operator decltype(Value)() const noexcept {
    return value;
  }
};

template<auto LHS, auto RHS>
struct Addition {
  static constexpr auto value = LHS + RHS;

  [[nodiscard]]
  constexpr operator decltype(value)() const noexcept {
    return value;
  }
};

template<auto LHS, auto RHS>
struct Subtraction {
  static constexpr auto value = LHS - RHS;

  [[nodiscard]]
  constexpr operator decltype(value)() const noexcept {
    return value;
  }
};

template<auto LHS, auto RHS>
struct Multiplication {
  static constexpr auto value = LHS * RHS;

  [[nodiscard]]
  constexpr operator decltype(value)() const noexcept {
    return value;
  }
};

template<auto LHS, auto RHS>
struct Division {
  static constexpr auto value = LHS / RHS;

  [[nodiscard]]
  constexpr operator decltype(value)() const noexcept {
    return value;
  }
};

template<auto LHS, auto RHS>
struct Equality {
  static constexpr BoolConstant<LHS == RHS> value {};

  [[nodiscard]]
  constexpr operator decltype(value)() const noexcept {
    return value;
  }
};

template<auto LHS, auto RHS>
struct LessThan {
  static constexpr BoolConstant < LHS<RHS> value {};

  [[nodiscard]]
  constexpr operator decltype(value)() const noexcept {
    return value;
  }
};

template<auto LHS, auto RHS>
struct GreaterThan {
  static constexpr BoolConstant<(LHS > RHS)> value {};

  [[nodiscard]]
  constexpr operator decltype(value)() const noexcept {
    return value;
  }
};

}
