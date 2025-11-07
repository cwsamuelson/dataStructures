#pragma once

#include "core/traits/impl/integral.hh"

#include <concepts>

namespace flp {

template<typename Type>
concept Integral = std::integral<Type>;
template<typename Type>
concept Signed = std::signed_integral<Type>;
template<typename Type>
concept Unsigned = std::unsigned_integral<Type>;
template<typename Type>
concept FloatingPoint = std::floating_point<Type>;

template<typename Type>
using MakeSigned = MakeSignedImpl<Type>::type;
template<typename Type>
using MakeUnsigned = MakeUnsignedImpl<Type>::type;

}
