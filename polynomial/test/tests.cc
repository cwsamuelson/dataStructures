#include <polynomial.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

TEST_CASE("`Polynomial` Coordinates") {
  SECTION("Dimensionality") {
    STATIC_CHECK(sizeof(Point1D<size_t>) == 1 * sizeof(size_t));
    STATIC_CHECK(sizeof(Point2D<size_t>) == 2 * sizeof(size_t));
    STATIC_CHECK(sizeof(Point3D<size_t>) == 3 * sizeof(size_t));
  }

  SECTION("Basic math operations") {
    constexpr Point2D<size_t> pt1 { 1, 1 };
    constexpr Point2D<size_t> pt2 { 2, 2 };
    constexpr Point2D<size_t> pt3 { 3, 3 };

    STATIC_CHECK(pt1 + pt2 == pt3);

    STATIC_CHECK(pt3 - pt1 == pt2);
    STATIC_CHECK(pt3 - pt2 == pt1);

    SECTION("Scaling") {
      constexpr Point2D<size_t> point { 1, 1 };
      constexpr Point2D<size_t> point5 { 5, 5 };

      STATIC_CHECK(point * 5 == point5);
      STATIC_CHECK(5 * point == point5);

      STATIC_CHECK(point5 / 5 == point);
    }
  }
}

TEST_CASE("`Polynomial`") {
  SECTION("basic") {
    /*Polynomial<> polynomial{1};

    STATIC_CHECK(polynomial(0) == 1);
    STATIC_CHECK(polynomial(1) == 1);
    STATIC_CHECK(polynomial(2) == 1);
    STATIC_CHECK(polynomial(3) == 1);*/
  }
}

