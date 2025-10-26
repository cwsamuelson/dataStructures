#pragma once

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

}
