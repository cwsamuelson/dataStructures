#pragma once

#include "core/traits/value_types.hh"

namespace flp {

namespace {

template<typename Type1, typename Type2>
struct SameAsImpl : FalseType {};

template<typename Type>
struct SameAsImpl<Type, Type> : TrueType {};

}

template<typename Type1, typename Type2>
concept SameAs = SameAsImpl<Type1, Type2>::value;

}
