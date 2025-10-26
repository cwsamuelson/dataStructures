#pragma once

#include "core/traits/value_types.hh"

#include <cstddef>

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

// ---

template<size_t Index, typename ...Args>
struct ArgGetImpl;

template<>
struct ArgGetImpl<0, void> {
  using type = void;
};

template<typename Type, typename ...Args, size_t Index>
struct ArgGetImpl<Index, Type, Args...> {
  using type = ArgGetImpl<Index - 1, Args...>::type;
};

template<typename Type, typename ...Args>
struct ArgGetImpl<0, Type, Args...> {
  using type = Type;
};

template<typename ...Args>
struct FunctionArguments {
  template<size_t Index>
  using get = ArgGetImpl<Index, Args...>::type;
  static constexpr size_t count = sizeof...(Args);
};

template<typename Functor>
struct FunctionTraits;

template<typename Return, typename ...Arguments>
struct FunctionTraits<Return(Arguments...)> {
  using result_type = Return;
  using arguments = FunctionArguments<Arguments...>;
  static constexpr auto argument_count = arguments::count;
};

}
