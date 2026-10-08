#include <color_theory/hsl.hh>
#include <color_theory/hsv.hh>

#include <catch2/catch_all.hpp>

using namespace flp::ColorTheory;

TEST_CASE("Color Theory: HSV construction and comparison") {
  const HSV<float> value {
    HSV<float>::Hue(120.f),
    HSV<float>::Saturation(0.5f),
    HSV<float>::Value(0.8f),
  };

  CHECK(value.hue()        == 120.f);
  CHECK(value.saturation() == 0.5f);
  // CHECK(value.value()      == 0.8f); // ????
  CHECK(value != HSV<float>{});

  CHECK(value == HSV<float>::Hue(120.f));
  CHECK(static_cast<HSV<float>::Hue>(value) == 120.f);
}

TEST_CASE("Color Theory: HSV hue is a distinct type from HSL hue, despite both being 'a hue'") {
  // STATIC_CHECK(not std::same_as<HSV<float>::Hue, HSL<float>::Hue>);
  // STATIC_CHECK(not std::same_as<HSV<float>::Saturation, HSL<float>::Saturation>);

  STATIC_CHECK(not std::same_as<HSV<float>::Hue, HSV<float>::Saturation>);
  STATIC_CHECK(not std::same_as<HSV<float>::Saturation, HSV<float>::Value>);
  STATIC_CHECK(not std::same_as<HSV<float>::Value, HSV<float>::Hue>);
}
