#pragma once

#include <expression.hh>

#include <concepts>
#include <functional>

namespace flp {

template<typename Type,
  std::derived_from<Expression<Type>> Expr,
  typename OP
>
struct GenericUnary : Expression<Type> {
  GenericUnary(Expr e, OP op)
    : expr(std::move(e))
    , operation(op)
  {}

  Expr expr;
  OP operation;

  [[nodiscard]]
  Type evaluate() const override {
    return operation(expr.evaluate());
  }
};

template<typename Expr, template<typename=void> typename OP>
using ArithmeticUnary = GenericUnary<
  decltype(std::declval<Expr>().evaluate()),
  Expr, OP<>
>;

// opposite of negate
// ...you find a better name
template<typename Type = void>
struct Posate {
  auto operator()(this auto&&, const Type& value) {
    return +value;
  }
};

template<>
struct Posate<void> {
  template<typename Type>
  auto operator()(this auto&&, const Type& value) {
    return +value;
  }
};

template<typename Type = void>
struct Deref {
  auto operator()(this auto&&, Type& value) {
    return *value;
  }
};

template<>
struct Deref<void> {
  template<typename Type>
  auto operator()(this auto&&, Type& value) {
    return *value;
  }
};

template<typename Expr>
auto operator+(Expr expr) {
  return ArithmeticUnary<Expr, Posate>(std::move(expr), {});
}

template<typename Expr>
auto operator-(Expr expr) {
  return ArithmeticUnary<Expr, std::negate>(std::move(expr), {});
}

template<typename Expr>
auto operator*(Expr expr) {
  return ArithmeticUnary<Expr, Deref>(std::move(expr), {});
}

}
