#include <color_theory/lab/lab.hh>

#include <catch2/catch_all.hpp>

using namespace flp::ColorTheory;

TEST_CASE("Color Theory: Lab construction and comparison") {
  const Lab<float> value{
    Lab<float>::Lightness(50.f),
    Lab<float>::A(10.f),
    Lab<float>::B(-10.f),
  };

  CHECK(value.l == Lab<float>::Lightness(50.f));
  CHECK(value.a == Lab<float>::A(10.f));
  CHECK(value.b == Lab<float>::B(-10.f));
  CHECK(value != Lab<float>{});
}

TEST_CASE("Color Theory: Lab channels are distinct types") {
  STATIC_CHECK(not std::same_as<Lab<float>::Lightness, Lab<float>::A>);
  STATIC_CHECK(not std::same_as<Lab<float>::A, Lab<float>::B>);
}
