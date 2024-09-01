#pragma once

namespace flp {

// is this useful with the existence of <=>?
template<typename LHS, typename RHS = LHS>
class comparitive {
public:
  using lhs_type = LHS;
  using rhs_type = RHS;

  [[nodiscard]]
  constexpr friend bool operator!=(const lhs_type& lhs, const rhs_type& rhs) noexcept {
    return !(lhs == rhs);
  }

  [[nodiscard]]
  constexpr friend bool operator>(const lhs_type& lhs, const rhs_type& rhs) noexcept {
    return !(lhs <= rhs);
  }

  [[nodiscard]]
  constexpr friend bool operator>=(const lhs_type& lhs, const rhs_type& rhs) noexcept {
    return !(lhs < rhs);
  }

  [[nodiscard]]
  constexpr friend bool operator<=(const lhs_type& lhs, const rhs_type& rhs) noexcept {
    return (lhs < rhs) || (lhs == rhs);
  }
};

}

