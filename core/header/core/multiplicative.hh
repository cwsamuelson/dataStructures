#pragma once

namespace flp {

template<typename LHS, typename RHS = LHS>
class multiplicative {
public:
  using lhs_type = LHS;
  using rhs_type = RHS;

  [[nodiscard]]
  constexpr friend auto operator*(lhs_type lhs, const rhs_type& rhs) noexcept {
    return (lhs *= rhs);
  }

  [[nodiscard]]
  constexpr friend auto operator/(lhs_type lhs, const rhs_type& rhs) noexcept {
    return (lhs /= rhs);
  }
};

}

