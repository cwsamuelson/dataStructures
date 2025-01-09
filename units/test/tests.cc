#include <measure.hh>
#include <measure_pack.hh>
//#include <units.hh>

#include <catch2/catch_all.hpp>

#include <concepts>

using namespace flp;

struct TestMeasure : MeasureBase {};

TEST_CASE("MeasurePack Has") {
  STATIC_CHECK(not MeasurePack<>::Has<int>);
  STATIC_CHECK(not MeasurePack<>::Has<float>);
  STATIC_CHECK(MeasurePack<1138>::Has<int>);
  STATIC_CHECK(not MeasurePack<1138>::Has<float>);
  STATIC_CHECK(MeasurePack<1138, 4.2F>::Has<int>);
  STATIC_CHECK(MeasurePack<1138, 4.2F>::Has<float>);
}

TEST_CASE("MeasurePack Select") {
  STATIC_CHECK(MeasurePack<1138>::Select<int> == 1138);
  STATIC_CHECK(MeasurePack<4.2F>::Select<float> == 4.2F);
  STATIC_CHECK(MeasurePack<1138, 4.2F>::Select<int> == 1138);
  STATIC_CHECK(MeasurePack<1138, 4.2F>::Select<float> == 4.2F);
}

TEST_CASE("MeasurePack UniqueTypes") {
  STATIC_CHECK(MeasurePack<>::UniqueTypes{} == MeasurePack<>{});
  STATIC_CHECK(MeasurePack<1138>::UniqueTypes{} == MeasurePack<1138>{});
  STATIC_CHECK(MeasurePack<4.2F>::UniqueTypes{} == MeasurePack<4.2F>{});
  STATIC_CHECK(MeasurePack<1138, 4.2F>::UniqueTypes{} == MeasurePack<1138, 4.2F>{});
  STATIC_CHECK(MeasurePack<11.38F, 4.2F>::UniqueTypes{} == MeasurePack<4.2F>{});
}

template<auto Value>
struct EmptyFilter {
  static constexpr auto value = Value.order != 0;
};

TEST_CASE("Measures") {
  SECTION("Empty measure") {
    Measure<> measure1;
    Measure<> measure2;

    STATIC_CHECK(std::same_as<decltype(measure1 * measure2), Measure<>>);
  }

  SECTION("Single measures") {
    Measure<TestMeasure { 1 }> measure1;
    Measure<>                  measure2;

    STATIC_CHECK(std::same_as<decltype(measure1 * measure2), decltype(measure1)>);
    //STATIC_CHECK(std::same_as<decltype(measure2 * measure1), decltype(measure1)>);

    STATIC_CHECK(std::same_as<decltype(measure1 * measure1), Measure<TestMeasure { 2 }>>);
    //STATIC_CHECK(std::same_as<decltype(measure2 * measure2), Measure<TestMeasure { 2 }>>);

    STATIC_CHECK(std::same_as<decltype(measure1 / measure2), decltype(measure1)>);
    //STATIC_CHECK(std::same_as<decltype(measure1 / measure1), Measure<>>);

    //STATIC_CHECK(std::same_as<decltype(measure2 / measure1), Measure<TestMeasure{-1}>>);
  }
}

TEST_CASE("Units") {}

