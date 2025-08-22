#include <point.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

TEST_CASE("`Point`") {
  constexpr Point<float, 2> p0;
  constexpr Point<float, 2> p1(1.f, 1.f);
  constexpr Point<float, 2> p2(2.f, 2.f);
  constexpr Vector<float, 2> v0;
  constexpr Vector<float, 2> v1(1.f, 1.f);

  STATIC_CHECK(p0 + v0 == p0);
  STATIC_CHECK(p1 + v0 == p1);
  STATIC_CHECK(p1 + v1 == Point<float, 2>{ 2.f, 2.f });
  STATIC_CHECK(p1 - p0 == Vector<float, 2>{ 1.f, 1.f });
  STATIC_CHECK(p2 + (p1 - p0) == Point<float, 2>{ 3.f, 3.f });
  STATIC_CHECK(p0 + (v0 + v1) == p1);
}
