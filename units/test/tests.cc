#include <units.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

TEST_CASE("Units") {}

TEST_CASE("Measures") {
  SECTION("Empty measure") {
    Measure<> measure1;
    Measure<> measure2;

    auto measure3 = measure1 * measure2;
    STATIC_CHECK(std::same_as<decltype(measure3), decltype(measure1)>);
  }
}
