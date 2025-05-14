#pragma once

//! @TODO multiple coordinate systems
//! @TODO multiple affine frames
//! @TODO conversion between origins/coordinate systems
//! @TODO homogeneous coordinates
// 4x4 matrices.  using 0./1. to distinguish
//! @TODO Variable dimensionality
namespace flp {

template<typename Type>
struct Point {
};

template<typename Type>
struct Vector {
};

template<typename Type>
constexpr Point<Type> O {};

// A basis vector is part of an affine reference frame
// or otherwise part of a coordinate system
// they represent the vectors defining the coordinate space
// a basis vector could be moved to another coordinate system,
// but its representation would not look the same, nor have
// the same foundational meaning.
template<typename Type, size_t AxisIndex>
using Basis = Vector<Type>;

template<typename Type>
constexpr Basis<Type, 0> i{/* 1, 0, 0 */};
template<typename Type>
constexpr Basis<Type, 1> j{/* 0, 1, 0 */};
template<typename Type>
constexpr Basis<Type, 2> k{/* 0, 0, 1 */};

struct AffineFrame {
  //origin;
  //bases;
};

// these operations define the affine nature of points and positions.
template<typename Type>
Point<Type> operator+(const Point<Type>&, const Vector<Type>&);
template<typename Type>
Vector<Type> operator-(const Point<Type>&, const Point<Type>&);

template<typename Type>
Vector<Type> operator+(const Vector<Type>&, const Vector<Type>&);
template<typename Type>
Vector<Type> operator-(const Vector<Type>&, const Vector<Type>&);

} // namespace flp

