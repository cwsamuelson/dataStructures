#pragma once

#include "core/traits/impl/reference.hh"

namespace flp {

template<typename Type>
using RemoveReference = RemoveReferenceImpl<Type>::type;

template<typename Type>
using AddLValueReference = Type&;

template<typename Type>
using AddRValueReference = Type&&;

template<typename Type>
static constexpr auto IsReference = IsReferenceImpl<Type>::value;

}
