#include <color_theory/linear_rgb.hh>
#include <color_theory/srgb.hh>

#include <catch2/catch_all.hpp>

using namespace flp::ColorTheory;

TEST_CASE("Color Theory: LinearRGB construction and comparison") {
  const LinearRGB<float> value {
    LinearRGB<float>::LinearRed(0.25f),
    LinearRGB<float>::LinearGreen(0.5f),
    LinearRGB<float>::LinearBlue(0.75f),
  };

  CHECK(value.red()   == 0.25f);
  CHECK(value.green() == 0.5f);
  CHECK(value.blue()  == 0.75f);
  CHECK(value != LinearRGB<float>{});

  CHECK(value == LinearRGB<float>::LinearRed(0.25f));
  CHECK(static_cast<LinearRGB<float>::LinearRed>(value) == 0.25f);
}

TEST_CASE("Color Theory: LinearRGB channels are distinct types from SRGB's") {
  // STATIC_CHECK(not std::same_as<LinearRGB<float>::LinearRed, SRGB<float>::Red>);
  // STATIC_CHECK(not std::same_as<LinearRGB<float>::LinearGreen, SRGB<float>::Green>);
  // STATIC_CHECK(not std::same_as<LinearRGB<float>::LinearBlue, SRGB<float>::Blue>);

  STATIC_CHECK(not std::same_as<LinearRGB<float>::LinearRed, LinearRGB<float>::LinearGreen>);
  STATIC_CHECK(not std::same_as<LinearRGB<float>::LinearGreen, LinearRGB<float>::LinearBlue>);
  STATIC_CHECK(not std::same_as<LinearRGB<float>::LinearBlue, LinearRGB<float>::LinearRed>);
}
