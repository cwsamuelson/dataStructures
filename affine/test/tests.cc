#include <point.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

TEST_CASE("`Point`") {
  constexpr Point<float, 2> p0;
  constexpr Point<float, 2> p1(1.f, 1.f);
  constexpr Vector<float, 2> v0;
  constexpr Vector<float, 2> v1(1.f, 1.f);

  STATIC_CHECK(p0 + v0 == p0);
  STATIC_CHECK(p1 + v0 == p1);
  STATIC_CHECK(p1 + v1 == Point<float, 2>{2.f, 2.f});
}
