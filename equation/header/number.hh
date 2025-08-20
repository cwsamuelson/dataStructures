#pragma once

#include <expression.hh>

namespace flp {

template<typename Type>
struct Value : Expression<Type> {
  Value(const Type& val)
    : value(val)
  {}

  Value(Type&& val)
    : value(std::move(val))
  {}

  [[nodiscard]]
  explicit
  operator Type() const noexcept {
    return value;
  }

  [[nodiscard]]
  Type evaluate() const override {
    return value;
  }

  Type value;
};

}
