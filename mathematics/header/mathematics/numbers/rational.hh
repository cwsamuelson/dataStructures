#pragma once

#include "mathematics/numbers/integer.hh"

namespace flp::Math {

struct Rational {
  Rational(const Integer&);
  Rational(const Integer&, const Integer&);

  Rational(const Rational&);

  // specifically NOT noexcept.  A value may not be integral.
  [[nodiscard]]
  explicit
  operator Integer() const;

  // built-in float, or something 'better'?
  // or both
  [[nodiscard]]
  explicit
  operator float() const noexcept;

  Integer numerator;
  Integer denominator;
};

}
