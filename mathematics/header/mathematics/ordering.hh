#pragma once

namespace flp::Math {

template<typename Type>
concept Equatable =
  requires(const Type& lhs, const Type& rhs) {
    { lhs == rhs } -> std::convertible_to<bool>;
    { lhs != rhs } -> std::convertible_to<bool>;
  };

// transitivity?
template<typename Type>
concept Ordered = Equatable<Type> and
  requires(const Type& lhs, const Type& rhs) {
    { lhs <  rhs } -> std::convertible_to<bool>;
    { lhs <= rhs } -> std::convertible_to<bool>;
    { lhs >  rhs } -> std::convertible_to<bool>;
    { lhs >= rhs } -> std::convertible_to<bool>;
  };

}
