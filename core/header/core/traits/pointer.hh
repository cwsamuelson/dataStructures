#pragma once

#include "core/traits/impl/pointer.hh"

namespace flp {

template<typename Type>
using RemovePointer = RemovePointerImpl<Type>::type;

template<typename Type>
using AddPointer = Type*;

template<typename Type>
static constexpr auto IsPointer = IsPointerImpl<Type>::value;

}
