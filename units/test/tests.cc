#include <measure.hh>
#include <standard_measures.hh>
#include <units.hh>
#include <value_set.hh>

#include <catch2/catch_all.hpp>

#include <concepts>

using namespace flp;

// must derive from, but not be `MeasureBase`
template<auto... Measures>
  requires(std::derived_from<decltype(Measures), MeasureBase> && ...)
      and ((not std::same_as<decltype(Measures), MeasureBase>) && ...)
struct TestMeasure {
  static constexpr typename Rebind<TypeSet<decltype(Measures)...>, std::tuple>::type measures {};

  template<auto... OtherMeasures>
  constexpr auto operator*(const TestMeasure<OtherMeasures...>& other) {
    constexpr auto f = []<typename Measure, typename Tuple>(const Measure& measure, const Tuple& tuple) {
      if constexpr (typename Rebind<Tuple, TypeSet>::type::template contains<Measure>()) {
        return measure + std::get<Measure>(tuple);
      } else {
        return measure;
      }
    };
    return TestMeasure<f(std::get<Measures>(measures), other)...> {};
  }
};

template<typename, template<auto...> typename, auto...>
struct RebindV;

template<template<auto...> typename Source, template<auto...> typename Target, auto... Args>
struct RebindV<Source<Args...>, Target> {
  using type = Target<Args...>;
};

TEST_CASE("experimental") {
  RebindV < Measure<LengthBase { 1 }, ValueSet>::type set;
}

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
