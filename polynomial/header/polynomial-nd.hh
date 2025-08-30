#pragma once

// to separate axes etc
#include <core/tagged_type.hh>

#include <cstddef>
#include <initializer_list>
#include <map>
#include <set>
#include <tuple>
#include <utility>
#include <vector>

namespace flp {

template<size_t N>
struct DimensionalityTag {};

template<typename Type, size_t N>
using NDimension = TaggedType<Type, DimensionalityTag<N>>;

template<typename Type>
using XDimension = NDimension<Type, 0>;
template<typename Type>
using YDimension = NDimension<Type, 1>;
template<typename Type>
using ZDimension = NDimension<Type, 2>;
template<typename Type>
using WDimension = NDimension<Type, 3>;

template<typename, typename>
struct NDPointImpl;

template<typename Type, size_t... DimensionIndices>
  requires(sizeof...(DimensionIndices) > 0)
struct NDPointImpl<Type, std::index_sequence<DimensionIndices...>> {
  // use an integer sequence
  using Coordinates = std::tuple<NDimension<Type, DimensionIndices>...>;

  constexpr NDPointImpl()                       = default;
  constexpr NDPointImpl(const NDPointImpl&)     = default;
  constexpr NDPointImpl(NDPointImpl&&) noexcept = default;

  constexpr NDPointImpl& operator=(const NDPointImpl&)     = default;
  constexpr NDPointImpl& operator=(NDPointImpl&&) noexcept = default;

  constexpr ~NDPointImpl() noexcept = default;

  friend constexpr auto operator<=>(const NDPointImpl&, const NDPointImpl&) noexcept = default;

  explicit constexpr NDPointImpl(Coordinates coords)
    : coordinates(std::move(coords)) {}

  template<typename... Args>
  explicit constexpr NDPointImpl(Args&&... args)
    : coordinates { std::forward<Args>(args)... } {}

  constexpr NDPointImpl operator-() const {
    return NDPointImpl((-std::get<DimensionIndices>(coordinates))...);
  }

  friend constexpr NDPointImpl operator+(const NDPointImpl& lhs, const NDPointImpl& rhs) {
    return NDPointImpl(
      std::make_tuple((std::get<DimensionIndices>(lhs.coordinates) + std::get<DimensionIndices>(rhs.coordinates))...));
  }

  friend constexpr NDPointImpl operator-(const NDPointImpl& lhs, const NDPointImpl& rhs) {
    return NDPointImpl(
      std::make_tuple((std::get<DimensionIndices>(lhs.coordinates) - std::get<DimensionIndices>(rhs.coordinates))...));
  }

  friend constexpr NDPointImpl operator*(const NDPointImpl& lhs, const Type& rhs) {
    return NDPointImpl(std::make_tuple((std::get<DimensionIndices>(lhs.coordinates) * rhs)...));
  }

  friend constexpr NDPointImpl operator*(const Type& lhs, const NDPointImpl& rhs) {
    return NDPointImpl(std::make_tuple((lhs * std::get<DimensionIndices>(rhs.coordinates))...));
  }

  friend constexpr NDPointImpl operator/(const NDPointImpl& lhs, const Type& rhs) {
    return NDPointImpl(std::make_tuple((std::get<DimensionIndices>(lhs.coordinates) / rhs)...));
  }

  friend constexpr NDPointImpl operator/(const Type& lhs, const NDPointImpl& rhs) {
    return NDPointImpl(std::make_tuple((lhs / std::get<DimensionIndices>(rhs.coordinates))...));
  }

  Coordinates coordinates;
};

template<typename Type, size_t Dimensionality>
using NDPoint = NDPointImpl<Type, std::make_index_sequence<Dimensionality>>;

template<typename Type>
using Point1D = NDPoint<Type, 1>;
template<typename Type>
using Point2D = NDPoint<Type, 2>;
template<typename Type>
using Point3D = NDPoint<Type, 3>;
template<typename Type>
using Point4D = NDPoint<Type, 4>;

template<typename Type, size_t Dimensionality>
struct PolyStorage {
  using type = std::map<NDPoint<size_t, Dimensionality>, Type>;
};

template<typename Type>
struct PolyStorage<Type, 1> {
  using type = std::vector<Type>;
};

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
//  However, this does not generalize: the general form of the plane is:
//  `x/a + y/b + z/c = 1`
//  which does not follow the above rule.

// is there a fast_float?
// float may be faster than double; imo faster is preferred
// leaving double for higher precision for now
// this absolutely should support u8/s8 etc
template<typename NumberType = double, size_t Dimensionality = 1>
struct PolynomialND {
  using PointType = NDPoint<NumberType, Dimensionality>;
  using Storage   = PolyStorage<NumberType, Dimensionality>::type;

  PolynomialND() = default;

  PolynomialND(std::initializer_list<PointType> coeffs);

  PolynomialND(const PolynomialND&)     = default;
  PolynomialND(PolynomialND&&) noexcept = default;

  PolynomialND& operator=(const PolynomialND&)     = default;
  PolynomialND& operator=(PolynomialND&&) noexcept = default;

  ~PolynomialND() = default;

  friend auto operator<=>(const PolynomialND&, const PolynomialND&) noexcept = default;

  PolynomialND& operator+();

  PolynomialND& operator+=(const PolynomialND&);
  PolynomialND& operator-=(const PolynomialND&);
  PolynomialND& operator*=(const PolynomialND&);
  PolynomialND& operator/=(const PolynomialND&);

  template<size_t OtherDimensionality>
  PolynomialND& operator*=(const PointType& value);
  template<size_t OtherDimensionality>
  PolynomialND& operator/=(const PointType& value);

  [[nodiscard]]
  PolynomialND operator-() const;

  [[nodiscard]] decltype(auto) operator[](const size_t index);

  template<size_t InputDimensionality>
  [[nodiscard]] decltype(auto) operator()(this auto&& self, const NDPoint<NumberType, InputDimensionality>& value);

  [[nodiscard]]
  std::set<NumberType> solve() const;

  [[nodiscard]]
  size_t order() const;

  [[nodiscard]]
  PolynomialND derive() const;
  [[nodiscard]]
  PolynomialND antiderive() const;
  [[nodiscard]]
  PolynomialND integrate(const NumberType upper_bound, const NumberType lower_bound) const;

private:
  std::vector<NumberType> coefficients;
};

} // namespace flp
