#include <intersection.hh>
#include <point.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

TEST_CASE("`Geometry`::`Point`") {
  Point<float> point;

  CHECK(point.x == .0f);
  CHECK(point.y == .0f);

  Point<float> point1;
  Point<float> point2;

  CHECK(point1 == point2);
  CHECK(intersections(point1, point2).at(0) == point1);
}
