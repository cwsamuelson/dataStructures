#pragma once

#include "core/traits/impl/const.hh"

namespace flp {

template<typename Type>
using RemoveConst = RemoveConstImpl<Type>::type;

template<typename Type>
using AddConst = const Type;

template<typename Type>
static constexpr auto IsConst = IsConstImpl<Type>::value;

}
