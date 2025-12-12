#pragma once

#include <concepts>

namespace flp::Math {

enum class WeakOrdering {
  Less,
  Equivalent,
  Greater,
};

enum class PartialOrdering {
  Less,
  Equivalent,
  Greater,
  Unordered,
};

enum class StrongOrdering {
  Less,
  Equivalent,
  Equal,
  Greater,
};

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

// transitivity?
template<typename Type>
concept PartiallyOrdered = Equatable<Type> and
  requires(const Type& lhs, const Type& rhs) {
    { lhs <  rhs } -> std::convertible_to<bool>;
    { lhs <= rhs } -> std::convertible_to<bool>;
    { lhs >  rhs } -> std::convertible_to<bool>;
    { lhs >= rhs } -> std::convertible_to<bool>;
  };

}
