#pragma once

// to separate axes etc
#include <core/tagged_type.hh>

#include <set>
#include <vector>

namespace flp {

// a polynomial is a 2D construct, inherently
// it translates one 1D value and maps it to another
// if I want to support potential higher dimensions:
//  the output is going to be the order of the polynomial - the order of the input
//  2D - 1D => 1D
//   a 2D curve, at an X location, produces a Y location
//  2D - 2D => bool
//   a 2D point can either be on or off a 2D curve
//  3D - 1D => 2D
//  a 3D surface, intersecting at a plane at a particular axis coordinate, will result in an intersecting 2D curve

// is there a fast_float?
// float may be faster than double; imo faster is preferred
// leaving double for higher precision for now
// this absolutely should support u8/s8 etc
template<typename NumberType = double>
struct Polynomial {
  Polynomial() = default;

  Polynomial(std::initializer_list<NumberType> coeffs);

  Polynomial(const Polynomial&) = default;
  Polynomial(Polynomial&&) noexcept = default;
  Polynomial& operator=(const Polynomial&) = default;
  Polynomial& operator=(Polynomial&&) noexcept = default;

  ~Polynomial() = default;

  friend auto operator<=>(const Polynomial&, const Polynomial&) noexcept = default;

  Polynomial& operator+=(const Polynomial&);
  Polynomial& operator-=(const Polynomial&);
  Polynomial& operator*=(const Polynomial&);
  Polynomial& operator/=(const Polynomial&);

  Polynomial& operator/=(const NumberType value);

  [[nodiscard]]
  Polynomial operator-() const;

  [[nodiscard]]
  decltype(auto) operator[](this auto&& self, const size_t index);

  [[nodiscard]]
  decltype(auto) operator()(const NumberType value) const;

  [[nodiscard]]
  std::set<NumberType> solve() const;

  [[nodiscard]]
  size_t order() const;

  // these may be subject to dimensionality
  // the derivative in a direction of a 3D surface, would result in a 2D curve
  // (I think?)
  // similar inverses for antiderivative and integration
  [[nodiscard]]
  Polynomial derive() const;
  [[nodiscard]]
  Polynomial antiderive() const;
  [[nodiscard]]
  void integrate(const NumberType upper_bound, const NumberType lower_bound) const;

private:
  std::vector<NumberType> coefficients;
};

} // namespace flp
