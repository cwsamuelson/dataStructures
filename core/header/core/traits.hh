#pragma once

#include "core/traits/const.hh"
#include "core/traits/function.hh"
#include "core/traits/integral.hh"
#include "core/traits/pointer.hh"
#include "core/traits/reference.hh"
#include "core/traits/value_types.hh"
#include "core/traits/volatile.hh"

#include <iterator>
#include <type_traits>

namespace flp {

// --- CV

template<typename Type>
using RemoveCV = RemoveConst<RemoveVolatile<Type>>;

template<typename Type>
using AddCV = AddConst<AddVolatile<Type>>;

// --- CV

template<typename Type>
static constexpr auto IsCV = IsConst<Type> and IsVolatile<Type>;

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

// --- Constexpr

template <typename Functor, auto Test = BoolConstant<(Functor{}, true)>::value>
consteval auto is_constexpr (Functor) {
  return Test;
}

} // namespace flp
