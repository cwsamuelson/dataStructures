#include <measure.hh>
#include <measure_pack.hh>
#include <standard_measures.hh>
#include <units.hh>
#include <value_set.hh>

#include <catch2/catch_all.hpp>

#include <concepts>

using namespace flp;

struct TestMeasure : MeasureBase {};

TEST_CASE("MeasurePack") {
  MeasurePack<TestMeasure { 1 }> pack;
}

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

TEST_CASE("Units") {}
