#pragma once

#include "mathematics/magma.hh"

#include <concepts>

namespace flp::Math {

template<typename Type>
concept Semigroup = Magma<Type>;

}
