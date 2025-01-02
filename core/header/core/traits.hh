#pragma once

#include <concepts>
#include <type_traits>

namespace flp {

// --- const

template<typename Type>
struct RemoveConstImpl {
  using type = Type;
};

template<typename Type>
struct RemoveConstImpl<const Type> {
  using type = Type;
};

template<typename Type>
using RemoveConst = RemoveConstImpl<Type>::type;

template<typename Type>
using AddConst = const Type;

// --- volatile

template<typename Type>
struct RemoveVolatileImpl {
  using type = Type;
};

template<typename Type>
struct RemoveVolatileImpl<volatile Type> {
  using type = Type;
};

template<typename Type>
using RemoveVolatile = RemoveVolatileImpl<Type>::type;

template<typename Type>
using AddVolatile = volatile Type;

// --- CV

template<typename Type>
using RemoveCV = RemoveConst<RemoveVolatile<Type>>;

template<typename Type>
using AddCV = AddConst<AddVolatile<Type>>;

// --- reference

template<typename Type>
struct RemoveReferenceImpl {
  using type = Type;
};

template<typename Type>
struct RemoveReferenceImpl<Type&> {
  using type = Type;
};

template<typename Type>
struct RemoveReferenceImpl<Type&&> {
  using type = Type;
};

template<typename Type>
using RemoveReference = RemoveReferenceImpl<Type>::type;

template<typename Type>
using AddLValueReference = Type&;

template<typename Type>
using AddRValueReference = Type&&;

// --- pointer

template<typename Type>
struct RemovePointerImpl {
  using type = Type;
};

template<typename Type>
struct RemovePointerImpl<Type*> {
  using type = Type;
};

template<typename Type>
struct RemovePointerImpl<Type* const> {
  using type = Type;
};

template<typename Type>
struct RemovePointerImpl<Type* const volatile> {
  using type = Type;
};

template<typename Type>
struct RemovePointerImpl<Type* volatile> {
  using type = Type;
};

template<typename Type>
using RemovePointer = RemovePointerImpl<Type>::type;

template<typename Type>
using AddPointer = Type*;

// --- Integral Constants

template<typename Type>
concept Integral = std::integral<Type>;

template<Integral Type, Type Value>
struct IntegralConstant {
  static constexpr Type value = Value;

  [[nodiscard]]
  constexpr operator Type() const noexcept {
    return value;
  }
};

template<bool Value>
using BoolConstant = IntegralConstant<bool, Value>;
using TrueType     = BoolConstant<true>;
using FalseType    = BoolConstant<false>;

// --- predicates

// These predicates are operating on values...
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

} // namespace flp
