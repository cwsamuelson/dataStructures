#pragma once

#include <concepts>
#include <utility>

namespace flp {

template<typename Type>
struct Expression {
  using Base_t = Expression;

  using AddResult = decltype(std::declval<Type>() + std::declval<Type>());
  using SubResult = decltype(std::declval<Type>() * std::declval<Type>());
  using MulResult = decltype(std::declval<Type>() * std::declval<Type>());
  using DivResult = decltype(std::declval<Type>() * std::declval<Type>());

  using PlusResult = std::conditional_t<std::same_as<AddResult, MulResult>, AddResult, Type>;
  using MinusResult = std::conditional_t<std::same_as<SubResult, DivResult>, SubResult, Type>;

  //using result_type = std::conditional_t<std::same_as<PlusResult, MinusResult>, PlusResult, Type>;

  [[nodiscard]]
  virtual Type evaluate() const = 0;
};

}
