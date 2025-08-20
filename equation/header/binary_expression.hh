#pragma once

#include <expression.hh>

#include <concepts>
#include <functional>

namespace flp {

template<typename Type,
  std::derived_from<Expression<Type>> LHS,
  std::derived_from<Expression<Type>> RHS,
  typename OP
>
struct GenericBinary : Expression<Type> {
  GenericBinary(LHS l, RHS r, OP op)
    : lhs(std::move(l))
    , rhs(std::move(r))
    , operation(op)
  {}

  LHS lhs;
  RHS rhs;
  OP operation;

  [[nodiscard]]
  Type evaluate() const override {
    return operation(lhs.evaluate(), rhs.evaluate());
  }
};

template<typename LHS, typename RHS, template<typename=void> typename OP>
using ArithmeticBinary = GenericBinary<
    std::common_type_t<
      decltype(std::declval<LHS>().evaluate()),
      decltype(std::declval<LHS>().evaluate())
    >, LHS, RHS, OP<>>;

template<typename LHS, typename RHS>
auto operator+(LHS lhs, RHS rhs) {
  return ArithmeticBinary<LHS, RHS, std::plus>(std::move(lhs), std::move(rhs), {});
}

template<typename LHS, typename RHS>
auto operator-(LHS lhs, RHS rhs) {
  return ArithmeticBinary<LHS, RHS, std::minus>(std::move(lhs), std::move(rhs), {});
}

template<typename LHS, typename RHS>
auto operator*(LHS lhs, RHS rhs) {
  return ArithmeticBinary<LHS, RHS, std::multiplies>(std::move(lhs), std::move(rhs), {});
}

template<typename LHS, typename RHS>
auto operator/(LHS lhs, RHS rhs) {
  return ArithmeticBinary<LHS, RHS, std::divides>(std::move(lhs), std::move(rhs), {});
}

template<typename LHS, typename RHS>
auto operator%(LHS lhs, RHS rhs) {
  return ArithmeticBinary<LHS, RHS, std::modulus>(std::move(lhs), std::move(rhs), {});
}

}
