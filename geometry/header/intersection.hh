#pragma once

#include <point.hh>
#include <line.hh>

#include <optional>
#include <vector>

namespace flp {

template<typename Type>
constexpr
bool intersects(const Point<Type>& p1, const Point<Type>& p2) {
  return p1 == p2;
}

template<typename Type>
constexpr
bool intersects(const Point<Type>& point, const Segment<Type>& segment) {
  return segment.contains(point);
}

template<typename Type>
constexpr
bool intersects(const Segment<Type>& segment, const Point<Type>& point) {
  return intersects(point, segment);
}

template<typename Type>
constexpr
std::optional<Point<Type>> intersection(const Line<Type>& line1, const Line<Type>& line2) {
  // y1 = m1x + b1
  // y2 = m2x + b2
  //
  // m1x + b1 = m2x + b2
  // m1x + (b1 - b2) = m2x
  // m2x - m1x = b1 - b2
  // x(m2 - m1) = (b1 - b2)
  // x = (b1 - b2) / (m2 - m1)
  const auto slope1 = line1.slope();
  const auto slope2 = line2.slope();

  if (slope1 == slope2) {
    return std::nullopt;
  }

  const auto offset1 = line1.center().y;
  const auto offset2 = line2.center().y;

  const auto x = (offset1 - offset2) / (slope2 - slope1);
  const auto y = (x * slope1) + offset1;
  return Point<Type>{x, y};
}

template<typename Type>
constexpr
std::optional<Point<Type>> intersection(const Segment<Type>& segment1, const Segment<Type>& segment2) {
  const auto point = intersection(Line<Type>{segment1.first, segment1.second}, Line<Type>{segment2.first, segment2.second});

  if (not point.has_value()) {
    return std::nullopt;
  }

  if (segment1.contains(point.value()) and segment2.contains(point.value())) {
    return point;
  }

  return std::nullopt;
}

}
