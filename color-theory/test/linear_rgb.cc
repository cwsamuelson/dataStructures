#include <color_theory/linear_rgb/linear_rgb.hh>
#include <color_theory/srgb/srgb.hh>

#include <catch2/catch_all.hpp>

using namespace flp::ColorTheory;

TEST_CASE("Color Theory: LinearRGB construction and comparison") {
  const LinearRGB<float> value{
    LinearRGB<float>::Red(0.25f),
    LinearRGB<float>::Green(0.5f),
    LinearRGB<float>::Blue(0.75f),
  };

  CHECK(value.red   == LinearRGB<float>::Red(0.25f));
  CHECK(value.green == LinearRGB<float>::Green(0.5f));
  CHECK(value.blue  == LinearRGB<float>::Blue(0.75f));

  CHECK(value != LinearRGB<float>{});
}

TEST_CASE("Color Theory: LinearRGB channels are distinct types from SRGB's") {
  STATIC_CHECK(not std::same_as<LinearRGB<float>::Red, SRGB<float>::Red>);
  STATIC_CHECK(not std::same_as<LinearRGB<float>::Green, SRGB<float>::Green>);
  STATIC_CHECK(not std::same_as<LinearRGB<float>::Blue, SRGB<float>::Blue>);
}
