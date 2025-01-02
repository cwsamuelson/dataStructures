#include <measure.hh>
#include <standard_measures.hh>
#include <units.hh>

#include <catch2/catch_all.hpp>

#include <concepts>

using namespace flp;

TEST_CASE("Units") {}

TEST_CASE("Measures") {
  SECTION("Empty measure") {
    Measure<> measure1;
    Measure<> measure2;

    STATIC_CHECK(std::same_as<decltype(measure1 * measure2), decltype(measure1)>);
  }

  SECTION("Single measures") {
    Measure<LengthBase { 1 }> measure1;
    Measure<>                 measure2;

    // STATIC_CHECK(std::same_as<decltype(measure1 * measure2), decltype(measure1)>);
    //  STATIC_CHECK(std::same_as < decltype(measure1 * measure1), Measure<LengthBase { 2 }>);
  }
}
