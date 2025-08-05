#pragma once

#include <utility>

namespace flp {

template<typename Type>
struct Value {
  Type value;

  explicit operator Type() const noexcept {
    return value;
  }

  Type evaluate() const noexcept {
    return value;
  }
};

template<typename LHS, typename RHS>
struct Addition {
  LHS lhs;
  RHS rhs;

  decltype(auto) evaluate() const noexcept(noexcept(lhs + rhs)) {
    return lhs.evaluate() + rhs.evaluate();
  }

  using Result = decltype(evaluate());

  explicit operator Result() const noexcept(noexcept(evaluate())) {
    return evaluate();
  }
};

template<typename LHS, typename RHS>
struct Subtraction {
  LHS lhs;
  RHS rhs;

  decltype(auto) evaluate() const noexcept(noexcept(lhs - rhs)) {
    return lhs.evaluate() - rhs.evaluate();
  }

  using Result = decltype(evaluate());

  explicit operator Result() const noexcept(noexcept(evaluate())) {
    return evaluate();
  }
};

template<typename LHS, typename RHS>
struct Multiplication {
  LHS lhs;
  RHS rhs;

  decltype(auto) evaluate() const noexcept(noexcept(lhs * rhs)) {
    return lhs.evaluate() * rhs.evaluate();
  }

  using Result = decltype(evaluate());

  explicit operator Result() const noexcept(noexcept(evaluate())) {
    return evaluate();
  }
};

template<typename LHS, typename RHS>
struct Division {
  LHS lhs;
  RHS rhs;

  decltype(auto) evaluate() const noexcept(noexcept(lhs / rhs)) {
    return lhs.evaluate() / rhs.evaluate();
  }

  using Result = decltype(evaluate());

  explicit operator Result() const noexcept(noexcept(evaluate())) {
    return evaluate();
  }
};

template<typename LHS, typename RHS>
struct Modulation {
  LHS lhs;
  RHS rhs;

  decltype(auto) evaluate() const noexcept(noexcept(lhs % rhs)) {
    return lhs.evaluate() % rhs.evaluate();
  }

  using Result = decltype(evaluate());

  explicit operator Result() const noexcept(noexcept(evaluate())) {
    return evaluate();
  }
};

template<typename Type>
struct Negation {
  Type value;

  decltype(auto) evaluate() const noexcept(noexcept(-value)) {
    return -value.evaluate();
  }

  using Result = decltype(evaluate());

  explicit operator Type() const noexcept(noexcept(evaluate())) {
    return evaluate();
  }
};

template<typename Type>
struct Posation { // idk what else to call this
  Type value;

  decltype(auto) evaluate() const noexcept(noexcept(+value)) {
    return +value.evaluate();
  }

  using Result = decltype(evaluate());

  explicit operator Type() const noexcept(noexcept(evaluate())) {
    return evaluate();
  }
};

template<typename Type>
struct PreIncrement {
  Type value;

  decltype(auto) evaluate() const noexcept(noexcept(++value)) {
    return ++value.evaluate();
  }

  using Result = decltype(evaluate());

  explicit operator Type() const noexcept(noexcept(evaluate())) {
    return evaluate();
  }
};

template<typename Type>
struct PostIncrement {
  Type value;

  decltype(auto) evaluate() const noexcept(noexcept(value++)) {
    return value.evaluate()++;
  }

  using Result = decltype(evaluate());

  explicit operator Type() const noexcept(noexcept(evaluate())) {
    return evaluate();
  }
};

template<typename Type>
struct PreDecrement {
  Type value;

  decltype(auto) evaluate() const noexcept(noexcept(--value)) {
    return --value.evaluate();
  }

  using Result = decltype(evaluate());

  explicit operator Type() const noexcept(noexcept(evaluate())) {
    return evaluate();
  }
};

template<typename Type>
struct PostDecrement {
  Type value;

  decltype(auto) evaluate() const noexcept(noexcept(value--)) {
    return value.evaluate()--;
  }

  using Result = decltype(evaluate());

  explicit operator Type() const noexcept(noexcept(evaluate())) {
    return evaluate();
  }
};

template<typename Type>
struct EnableExprTempl;

template<typename LHS, typename RHS>
Addition<LHS, RHS> operator+(LHS&& lhs, RHS&& rhs) noexcept
  requires requires() {
    {lhs + rhs};
  } and requires() {
    EnableExprTempl<LHS>{};
    EnableExprTempl<RHS>{};
  } {
  return { std::forward<LHS>(lhs), std::forward<RHS>(rhs) };
}

}
