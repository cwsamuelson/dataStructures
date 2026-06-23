#pragma once

namespace flp::Math {

struct Rational;

struct Integer {
  [[nodiscard]]
  friend
  Rational operator/(const Integer&, const Integer&) noexcept;
};

}
