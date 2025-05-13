#pragma once

#include <expression.hh>

#include <concepts>

namespace flp {

template<typename Type, std::derived_from<Expression> LHS, std::derived_from<Expression> RHS>
struct BinaryExpression : Expression<Type> {
  LHS lhs;
  RHS rhs;
};

namespace {
template<typename Type, typename LHS, typename RHS, typename OP>
struct GenericBinary : BinaryExpression<Type, LHS, RHS> {
  OP operation;

  Base_t::result_type evaluate() const override {
    return operation(lhs.evaluate(), rhs.evaluate());
  }
};
}

template<typename Type, std::derived_from<Expression> LHS, std::derived_from<Expression> RHS>
using AdditionExpression = GenericBinary<Type, LHS, RHS, std::plus<>>;

template<std::derived_from<Expression> LHS, std::derived_from<Expression> RHS>
auto operator+(LHS lhs, RHS rhs) {
  return AdditionExpression(std::move(lhs), std::move(rhs));
}

}
