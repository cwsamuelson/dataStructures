#include<string>

#define CATCH_CONFIG_MAIN
#include<catch2/catch.hpp>

#include<spline.hh>

using namespace std;

namespace gsw {

template<typename OSTREAM>
OSTREAM& operator<<(OSTREAM& os, const gsw::point2d& p)
{
  os << "{x: " << p.x << ",\ty: " << p.y << "}";
  return os;
}

}

TEST_CASE("Manual point insertion", "[spline]"){
  gsw::spline s;

  SECTION("Xs")
  {
    s.push_back({ 0, 0 });
    s.push_back({ 1, 0 });
    s.push_back({ 2, 0 });
    s.push_back({ 3, 0 });

    CHECK(s.point(1.0) == gsw::point2d{1.0f, 0.0f});
    CHECK(s.point(2.0) == gsw::point2d{2.0f, 0.0f});
    CHECK(s.point(3.0) == gsw::point2d{3.0f, 0.0f});
  }

  SECTION("Ys")
  {
    s.push_back({ 0, 0 });
    s.push_back({ 0, 1 });
    s.push_back({ 0, 2 });
    s.push_back({ 0, 3 });

    CHECK(s.point(1.0) == gsw::point2d{0.0f, 1.0f});
    CHECK(s.point(2.0) == gsw::point2d{0.0f, 2.0f});
    CHECK(s.point(3.0) == gsw::point2d{0.0f, 3.0f});
  }

  SECTION("Xs Ys")
  {
    s.push_back({ 0, 0 });
    s.push_back({ 1, 1 });
    s.push_back({ 2, 2 });
    s.push_back({ 3, 3 });

    CHECK(s.point(1.0) == gsw::point2d{ 1.0f, 1.0f });
    CHECK(s.point(2.0) == gsw::point2d{ 2.0f, 2.0f });
    CHECK(s.point(3.0) == gsw::point2d{ 3.0f, 3.0f });
  }
}

TEST_CASE("Initialized with points", "[spline]")
{
  SECTION("Xs")
  {
    gsw::spline s{ { 0, 0 },
                   { 1, 0 },
                   { 2, 0 },
                   { 3, 0 } };

    CHECK(s.point(1.0) == gsw::point2d{ 1.0f, 0.0f });
    CHECK(s.point(2.0) == gsw::point2d{ 2.0f, 0.0f });
    CHECK(s.point(3.0) == gsw::point2d{ 3.0f, 0.0f });
  }

  SECTION("Ys")
  {
    gsw::spline s{ { 0, 0 },
                   { 0, 1 },
                   { 0, 2 },
                   { 0, 3 } };

    CHECK(s.point(1.0) == gsw::point2d{ 0.0f, 1.0f });
    CHECK(s.point(2.0) == gsw::point2d{ 0.0f, 2.0f });
    CHECK(s.point(3.0) == gsw::point2d{ 0.0f, 3.0f });
  }

  SECTION("Xs Ys")
  {
    gsw::spline s{ { 0, 0 },
                   { 1, 1 },
                   { 2, 2 },
                   { 3, 3 } };

    CHECK(s.point(1.0) == gsw::point2d{ 1.0f, 1.0f });
    CHECK(s.point(2.0) == gsw::point2d{ 2.0f, 2.0f });
    CHECK(s.point(3.0) == gsw::point2d{ 3.0f, 3.0f });
  }
}
