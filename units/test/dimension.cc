#include <dimension.hh>
#include <dimension_pack.hh>
//#include <units.hh>

#include <catch2/catch_all.hpp>

#include <concepts>

using namespace flp;

struct TestDimension1 : DimensionBase {};
struct TestDimension2 : DimensionBase {};

TEST_CASE("DimensionPack Has") {
  STATIC_CHECK(not DimensionPack<>::Has<int>);
  STATIC_CHECK(not DimensionPack<>::Has<float>);
  STATIC_CHECK(DimensionPack<1138>::Has<int>);
  STATIC_CHECK(not DimensionPack<1138>::Has<float>);
  STATIC_CHECK(DimensionPack<1138, 4.2F>::Has<int>);
  STATIC_CHECK(DimensionPack<1138, 4.2F>::Has<float>);
}

TEST_CASE("DimensionPack Select") {
  STATIC_CHECK(DimensionPack<1138>::Select<int> == 1138);
  STATIC_CHECK(DimensionPack<4.2F>::Select<float> == 4.2F);
  STATIC_CHECK(DimensionPack<1138, 4.2F>::Select<int> == 1138);
  STATIC_CHECK(DimensionPack<1138, 4.2F>::Select<float> == 4.2F);
}

TEST_CASE("DimensionPack UniqueTypes") {
  STATIC_CHECK(DimensionPack<>::UniqueTypes{} == DimensionPack<>{});
  STATIC_CHECK(DimensionPack<1138>::UniqueTypes{} == DimensionPack<1138>{});
  STATIC_CHECK(DimensionPack<4.2F>::UniqueTypes{} == DimensionPack<4.2F>{});
  STATIC_CHECK(DimensionPack<1138, 4.2F>::UniqueTypes{} == DimensionPack<1138, 4.2F>{});
  STATIC_CHECK(DimensionPack<11.38F, 4.2F>::UniqueTypes{} == DimensionPack<4.2F>{});
}

template<auto Value>
struct EmptyFilter {
  static constexpr auto value = Value.order != 0;
};

TEST_CASE("Dimensions") {
  SECTION("Empty Dimension") {
    Dimension<> dimension1;
    Dimension<> dimension2;

    STATIC_CHECK(std::same_as<decltype(dimension1 * dimension2), Dimension<>>);
  }

  SECTION("Single dimensions") {
    Dimension<TestDimension1 { 1 }> dimension1;
    Dimension<>                  dimension2;

    STATIC_CHECK(dimension1 * dimension2 == dimension1);
    STATIC_CHECK(dimension2 * dimension1 == dimension1);

    STATIC_CHECK(dimension1 * dimension1 == Dimension<TestDimension1{2}>{});
    STATIC_CHECK(dimension2 * dimension2 == Dimension<>{});

    STATIC_CHECK(dimension1 / dimension2 == dimension1);
    STATIC_CHECK(dimension1 / dimension1 == Dimension<>{});

    STATIC_CHECK(dimension2 / dimension1 == Dimension<TestDimension1{-1}>{});
    STATIC_CHECK(dimension2 / dimension2 == Dimension<>{});
  }

  SECTION("Multiple dimensions") {
    Dimension<TestDimension1{1}> dimension1;
    Dimension<TestDimension2{1}> dimension2;
    auto dimension3 = dimension1 / dimension2;

    STATIC_CHECK(dimension3 * dimension2 == dimension1);

    Dimension<TestDimension1{1}, TestDimension2{-1}> dimension4{};
    STATIC_CHECK(dimension4 * dimension2 == dimension1);

    STATIC_CHECK(dimension4 * dimension4 == Dimension<TestDimension1{2}, TestDimension2{-2}>{});
  }
}

