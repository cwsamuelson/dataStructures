#define CATCH_CONFIG_MAIN
#include<catch2/catch.hpp>

#include <named_point.hh>

TEST_CASE("Named point testing", "[named]")
{
  gsw::point1 p1_1 = {1.0};
  gsw::point1 p1_2(2.0);
  gsw::point1 p1_3{3.0};

  p1_1 = p1_2;

  gsw::point2 p2_1 = {0.0, 1.0};
  gsw::point2 p2_2{0.0, 2.0};
  gsw::point2 p2_3{{0.0, 3.0}};
}

