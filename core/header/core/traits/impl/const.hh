#pragma once

#include "core/traits/value_types.hh"

namespace flp {

namespace {

// modify

template<typename Type>
struct RemoveConstImpl {
  using type = Type;
};

template<typename Type>
struct RemoveConstImpl<const Type> {
  using type = Type;
};

// query

template<typename>
struct IsConstImpl {
  static constexpr auto value = False;
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

}

}
