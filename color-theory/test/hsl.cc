#include <color_theory/hsl/hsl.hh>

#include <catch2/catch_all.hpp>

using namespace flp::ColorTheory;

TEST_CASE("Color Theory: HSL construction and comparison") {
  const HSL<float> value{
    HSL<float>::Hue(240.f),
    HSL<float>::Saturation(0.4f),
    HSL<float>::Lightness(0.6f),
  };

  CHECK(value.hue        == HSL<float>::Hue(240.f));
  CHECK(value.saturation == HSL<float>::Saturation(0.4f));
  CHECK(value.lightness  == HSL<float>::Lightness(0.6f));
  CHECK(value != HSL<float>{});
}

TEST_CASE("Color Theory: HSL channels are distinct types") {
  STATIC_CHECK(not std::same_as<HSL<float>::Hue, HSL<float>::Saturation>);
  STATIC_CHECK(not std::same_as<HSL<float>::Saturation, HSL<float>::Lightness>);
}
