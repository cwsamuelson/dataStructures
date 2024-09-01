#pragma once

#include "core/concepts.hh"

namespace flp {

template<typename LHS, typename RHS = LHS>
class additive {
public:
  using lhs_type = LHS;
  using rhs_type = RHS;

  [[nodiscard]]
  constexpr friend decltype(auto) operator+(lhs_type lhs, const rhs_type& rhs) noexcept {
    return (lhs += rhs);
  }

  [[nodiscard]]
  constexpr friend decltype(auto) operator-(lhs_type lhs, const rhs_type& rhs) noexcept {
    return (lhs -= rhs);
  }
};

}

