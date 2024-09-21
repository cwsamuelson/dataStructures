#include <polynomial.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

TEST_CASE("Coordinates") {
  SECTION("Dimensionality") {
    STATIC_CHECK(sizeof(Point1D<size_t>) == 1 * sizeof(size_t));
    STATIC_CHECK(sizeof(Point2D<size_t>) == 2 * sizeof(size_t));
    STATIC_CHECK(sizeof(Point3D<size_t>) == 3 * sizeof(size_t));
  }

  SECTION("Basic math operations") {
    Point2D<size_t> pt1 { 1, 1 };
    Point2D<size_t> pt2 { 2, 2 };
    Point2D<size_t> pt3 { 3, 3 };

    CHECK(pt1 + pt2 == pt3);

    CHECK(pt3 - pt1 == pt2);
    CHECK(pt3 - pt2 == pt1);

    SECTION("Scaling") {
      Point2D<size_t> point { 1, 1 };
      Point2D<size_t> point5 { 5, 5 };

      CHECK(point * 5 == point5);
      CHECK(5 * point == point5);

      CHECK(point5 / 5 == point);
    }
  }
}

TEST_CASE("Polynomial") {}
