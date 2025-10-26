#pragma once

#include "core/traits/integral.hh"

namespace flp {

template<auto Value>
struct ValueConstant {
  using Type = decltype(Value);

  static constexpr Type value = Value;

  [[nodiscard]]
  constexpr operator Type() const noexcept {
    return value;
  }
};

template<auto Value>
  requires Integral<decltype(Value)>
using IntegralConstant = ValueConstant<Value>;

template<auto Value>
  requires Signed<decltype(Value)>
using SignedConstant = ValueConstant<Value>;

template<auto Value>
  requires Unsigned<decltype(Value)>
using UnsignedConstant = ValueConstant<Value>;

template<auto Value>
  requires FloatingPoint<decltype(Value)>
using FloatingPointConstant = ValueConstant<Value>;

template<bool Value>
using BoolConstant = ValueConstant<Value>;
using TrueType     = BoolConstant<true>;
using FalseType    = BoolConstant<false>;

static constexpr TrueType True{};
static constexpr FalseType False{};

}
