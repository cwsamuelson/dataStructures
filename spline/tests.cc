#include<string>

#define CATCH_CONFIG_MAIN
#include<catch2/catch.hpp>

#include<spline.hh>

using namespace std;

TEST_CASE("Manual point insertion", "[spline]"){
  gsw::spline s;

  s.points.push_back({0, 0});
  s.points.push_back({1, 0});
  s.points.push_back({2, 0});
  s.points.push_back({3, 0});

  CHECK(s.point(1.5) == gsw::point2d{0.5f, 0.0f});
}

TEST_CASE("Initialized with points", "[spline]")
{
  gsw::spline s{{0, 0}, {1, 0}, {2, 0}};

  CHECK(s.point(1.5) == gsw::point2d{0.5f, 0.0f});
}
