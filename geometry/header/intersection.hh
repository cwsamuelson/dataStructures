#pragma once

#include <point.hh>
#include <line.hh>

#include <vector>

namespace flp {

template<typename Type>
std::vector<Point<Type>> intersections(const Point<Type>& p1, const Point<Type>& p2) {
  if (p1 == p2) {
    return {p1};
  } else {
    return {};
  }
}

template<typename Type>
std::vector<Point<Type>> intersections(const Point<Type>&, const Segment<Type>&) {
  return {};
}

template<typename Type>
std::vector<Point<Type>> intersections(const Segment<Type>& segment, const Point<Type>& point) {
  return intersections(point, segment);
}

template<typename Type>
std::vector<Point<Type>> intersections(const Segment<Type>& segment1, const Segment<Type>& segment2) {
  return {};
}

}
