#pragma once

#include "core/traits/impl/volatile.hh"

namespace flp {

template<typename Type>
using RemoveVolatile = RemoveVolatileImpl<Type>::type;

template<typename Type>
using AddVolatile = volatile Type;

template<typename Type>
static constexpr auto IsVolatile = IsVolatileImpl<Type>::value;

}
