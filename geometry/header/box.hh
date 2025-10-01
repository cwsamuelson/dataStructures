#pragma once

#include <point.hh>

#include <array>

namespace flp {

template<typename Type = float>
struct AxisAlignedBoundingBox {
  Point<Type> first{};
  Point<Type> second{};

  friend
  constexpr
  bool operator==(const AxisAlignedBoundingBox&, const AxisAlignedBoundingBox&) noexcept = default;
};

template<typename Type = float>
using AABB = AxisAlignedBoundingBox<Type>;

template<typename Type = float>
using Box = AxisAlignedBoundingBox<Type>;

template<typename Type = float>
struct Rectangle {
  std::array<Point<Type>, 4> points{};

  friend
  constexpr
  bool operator==(const Rectangle&, const Rectangle&) noexcept = default;
};

template<typename Type = float>
using Rect = Rectangle<Type>;

} // namespace flp
