#pragma once

#include "core/traits/value_types.hh"

namespace flp {

namespace {

// modify

template<typename Type>
struct RemoveVolatileImpl {
  using type = Type;
};

template<typename Type>
struct RemoveVolatileImpl<volatile Type> {
  using type = Type;
};

// query

template<typename>
struct IsVolatileImpl {
  static constexpr auto value = False;
};

template<typename Type>
struct IsVolatileImpl<volatile Type> {
  static constexpr auto value = True;
};

}

}
