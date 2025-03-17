#pragma once

#include <concepts>
#include <iterator>
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
template<typename Type>
concept Signed = std::signed_integral<Type>;
template<typename Type>
concept Unsigned = std::unsigned_integral<Type>;
template<typename Type>
concept FloatingPoint = std::floating_point<Type>;

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

// --- const

template<typename>
struct IsConstImpl {
  static constexpr auto value = FalseType{};
};

template<typename Type>
struct IsConstImpl<const Type> {
  static constexpr auto value = True;
};

template<typename Type>
struct IsConstImpl<Type*> {
  static constexpr auto value = IsConstImpl<Type>::value;
};

template<typename Type>
struct IsConstImpl<Type&> {
  static constexpr auto value = IsConstImpl<Type>::value;
};

template<typename Type>
struct IsConstImpl<Type&&> {
  static constexpr auto value = IsConstImpl<Type>::value;
};

template<typename Type>
static constexpr auto IsConst = IsConstImpl<Type>::value;

// --- volatile

template<typename>
struct IsVolatileImpl {
  static constexpr auto value = FalseType{};
};

template<typename Type>
struct IsVolatileImpl<volatile Type> {
  static constexpr auto value = True;
};

template<typename Type>
static constexpr auto IsVolatile = IsVolatileImpl<Type>::value;

// --- CV

template<typename Type>
static constexpr auto IsCV = IsConst<Type> and IsVolatile<Type>;

// --- reference

template<typename>
struct IsReferenceImpl {
  static constexpr auto value = FalseType{};
};

template<typename Type>
struct IsReferenceImpl<Type&&> {
  static constexpr auto value = True;
};

template<typename Type>
struct IsReferenceImpl<Type&> {
  static constexpr auto value = True;
};

template<typename Type>
static constexpr auto IsReference = IsReferenceImpl<Type>::value;

// --- pointer

template<typename>
struct IsPointerImpl {
  static constexpr auto value = FalseType{};
};

template<typename Type>
struct IsPointerImpl<Type*> {
  static constexpr auto value = TrueType{};
};

template<typename Type>
static constexpr auto IsPointer = IsPointerImpl<Type>::value;

// --- iterator

template<typename Type>
using IteratorType = decltype(*std::declval<Type>());

// --- range

template<typename Type>
using RangeIterator = decltype(std::begin(std::declval<Type>()));

template<typename Type>
using RangeType = IteratorType<RangeIterator<Type>>;

// --- If

template<bool Condition>
struct If {
  struct Then {
  };
  struct Else {
  };
};

// --- Map

} // namespace flp

