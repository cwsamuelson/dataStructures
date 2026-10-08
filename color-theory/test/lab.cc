#include <color_theory/lab.hh>

#include <catch2/catch_all.hpp>

using namespace flp::ColorTheory;

TEST_CASE("Color Theory: Lab construction and comparison") {
  const LAB<float> value {
    LAB<float>::Lightness(50.f),
    LAB<float>::A(10.f),
    LAB<float>::B(-10.f),
  };

   CHECK(value.l() == 50.f);
   CHECK(value.a() == 10.f);
   CHECK(value.b() == -10.f);
   CHECK(value != LAB<float>{});
}

TEST_CASE("Color Theory: Lab channels are distinct types") {
  STATIC_CHECK(not std::same_as<LAB<float>::Lightness, LAB<float>::A>);
  STATIC_CHECK(not std::same_as<LAB<float>::A, LAB<float>::B>);
  STATIC_CHECK(not std::same_as<LAB<float>::Lightness, LAB<float>::B>);
}
