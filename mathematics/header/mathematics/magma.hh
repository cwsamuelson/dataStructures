#pragma once

#include <concepts>

namespace flp::Math {

template<typename Type>
concept Magma = requires(const Type& lhs, const Type& rhs) {
  { closure(lhs, rhs) } -> std::same_as<Type>;
};

}
