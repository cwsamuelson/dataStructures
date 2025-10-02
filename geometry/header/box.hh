#pragma once

#include <point.hh>

#include <array>

namespace flp {

// - bounded
// - aligned
template<typename Type = float>
struct AxisAlignedBoundingBox {
  Point<Type> first{};
  Point<Type> second{};

  [[nodiscard]]
  constexpr
  Point<Type> center() const noexcept {
    return (second - first) / 2;
  }

  friend
  constexpr
  bool operator==(const AxisAlignedBoundingBox&, const AxisAlignedBoundingBox&) noexcept = default;
};

template<typename Type = float>
using AABB = AxisAlignedBoundingBox<Type>;

template<typename Type = float>
using Box = AxisAlignedBoundingBox<Type>;

// - bounded
// - unaligned
template<typename Type = float>
struct Rectangle {
  std::array<Point<Type>, 4> points{};

  friend
  constexpr
  bool operator==(const Rectangle&, const Rectangle&) noexcept = default;
};

template<typename Type = float>
using Rect = Rectangle<Type>;

// - unbounded
// - unaligned
template<typename Type = float>
struct Plane {
  std::array<Point<Type>, 3> points{};

  Plane(const Rectangle<Type>&);
  Plane(const AxisAlignedBoundingBox<Type>&);
};

} // namespace flp
