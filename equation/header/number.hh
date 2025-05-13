#pragma once

#include <expression.hh>

namespace flp {

template<typename Type>
struct Value : Expression<Type> {
  Type value;

  auto evaluate() const override {
    return value;
  }
};

}
