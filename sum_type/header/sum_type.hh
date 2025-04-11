#pragma once

#include "core/concepts.hh"

#include <type_traits>
#include <variant>

namespace flp {

// how to express the association between a 'Types' type and a 'Value' enum value
// When setting a particular 'Value' value, then the associated type will be necessary.

template<typename ValueEnum, ValueEnum>
struct Y {
};

template<typename ValueEnum, ValueEnum, typename>
struct Z {
};

template<typename ValueEnum, typename ...Args>
  requires ((IsSpecializationOf<Args, Y> or IsSpecializationOf<Args, Z>) && ...)
struct X{};

//template<typename ValueEnum, ValueEnum, bool>
//struct TypePair;
//
//template<typename ValueEnum, ValueEnum Value>
//struct TypePair<ValueEnum, Value, false> {
//  static constexpr auto value = Value;
//};
//
//template<typename ValueEnum, ValueEnum Value, typename Type>
//struct TypePair<ValueEnum, Value, true> {
//  using type = Type;
//  static constexpr auto value = Value;
//};

template<typename Value, typename ...Types>
  requires std::is_enum_v<Value>
struct SumType {
  Value current_value;
  std::variant<std::monostate, Types...> value;
};

} // namespace flp

