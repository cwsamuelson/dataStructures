#include <measure.hh>
#include <measure_pack.hh>
//#include <units.hh>

#include <catch2/catch_all.hpp>

#include <concepts>

using namespace flp;

struct TestMeasure1 : MeasureBase {};
struct TestMeasure2 : MeasureBase {};

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
    Measure<TestMeasure1 { 1 }> measure1;
    Measure<>                  measure2;

    STATIC_CHECK(measure1 * measure2 == measure1);
    STATIC_CHECK(measure2 * measure1 == measure1);

    STATIC_CHECK(measure1 * measure1 == Measure<TestMeasure1{2}>{});
    STATIC_CHECK(measure2 * measure2 == Measure<>{});

    STATIC_CHECK(measure1 / measure2 == measure1);
    STATIC_CHECK(measure1 / measure1 == Measure<>{});

    STATIC_CHECK(measure2 / measure1 == Measure<TestMeasure1{-1}>{});
    STATIC_CHECK(measure2 / measure2 == Measure<>{});
  }

  SECTION("Multiple measures") {
    Measure<TestMeasure1{1}> measure1;
    Measure<TestMeasure2{1}> measure2;
    auto measure3 = measure1 / measure2;

    STATIC_CHECK(measure3 * measure2 == measure1);

    Measure<TestMeasure1{1}, TestMeasure2{-1}> measure4{};
    STATIC_CHECK(measure4 * measure2 == measure1);

    STATIC_CHECK(measure4 * measure4 == Measure<TestMeasure1{2}, TestMeasure2{-2}>{});
  }
}

TEST_CASE("Units") {}

