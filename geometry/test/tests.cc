#include <intersection.hh>
#include <point.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

TEST_CASE("`Geometry`::`Point`") {
  constexpr Point<float> point;

  STATIC_CHECK(point.center() == point);

  STATIC_CHECK(point.x == .0f);
  STATIC_CHECK(point.y == .0f);

  constexpr Point<float> point1;
  constexpr Point<float> point2;

  STATIC_CHECK(point1 == point2);
  STATIC_CHECK(intersects(point1, point2));
}

TEST_CASE("`Geometry`::`Line`") {
  constexpr Line pline{ {.0f, .0f}, {1.f, 1.f} };
  constexpr Point ppoint{.0f, 1.f};

  STATIC_CHECK(pline.length() == std::numeric_limits<float>::infinity());
  STATIC_CHECK(pline.slope() == 1.f);
  STATIC_CHECK(pline.center().x == .0f);

  STATIC_CHECK(ppoint.center() == ppoint);

  STATIC_CHECK(ppoint >  pline);
  STATIC_CHECK(ppoint >= pline);

  constexpr Point npoint{.0f, -1.f};

  STATIC_CHECK(npoint <  pline);
  STATIC_CHECK(npoint <= pline);

  constexpr Line nline{ {.0f, .0f}, {1.f, -1.f} };

  STATIC_CHECK(nline.length() == std::numeric_limits<float>::infinity());
  STATIC_CHECK(nline.slope() == -1.f);
  STATIC_CHECK(nline.center().x == .0f);

  constexpr auto ipoint = intersection(nline, pline);

  STATIC_CHECK(ipoint.has_value());
  STATIC_CHECK(ipoint.value() == Point{0.f, 0.f});
}

TEST_CASE("`Geometry`::`Segment`") {
  constexpr Segment segment1{ {-1.f, 0.f}, {5.f, 0.f} };
  constexpr Point<float> point;

  STATIC_CHECK(segment1.length() == 6.f);
  STATIC_CHECK(segment1.slope() == 0.f);
  STATIC_CHECK(segment1.center() == Point{2.f, 0.f});

  constexpr Segment segment2{ {0.f, -1.f}, {0.f, 1.f} };

  STATIC_CHECK(segment2.length() == 2.f);
  STATIC_CHECK(segment2.slope() == std::numeric_limits<float>::infinity());
  STATIC_CHECK(segment2.center() == Point{0.f, 0.f});

  constexpr auto ipoint = intersection(segment1, segment2);

  STATIC_CHECK(ipoint.has_value());
  STATIC_CHECK(ipoint.value() == Point{0.f, 0.f});
}
