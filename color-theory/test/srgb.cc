#include <color_theory/linear_rgb/linear_rgb.hh>
#include <color_theory/srgb/srgb.hh>

#include <catch2/catch_all.hpp>

using namespace flp::ColorTheory;

TEST_CASE("Color Theory: SRGB construction and comparison") {
  const SRGB<float> white{SRGB<float>::Red(1.f), SRGB<float>::Green(1.f), SRGB<float>::Blue(1.f)};
  const SRGB<float> black{};

  CHECK(white.red   == SRGB<float>::Red(1.f));
  CHECK(white.green == SRGB<float>::Green(1.f));
  CHECK(white.blue  == SRGB<float>::Blue(1.f));

  CHECK(black.red   == SRGB<float>::Red(0.f));
  CHECK(black.green == SRGB<float>::Green(0.f));
  CHECK(black.blue  == SRGB<float>::Blue(0.f));

  CHECK(white != black);
  CHECK(black == SRGB<float>{});
}

TEST_CASE("Color Theory: SRGB channels are distinct types from each other and from LinearRGB") {
  STATIC_CHECK(not std::same_as<SRGB<float>::Red, SRGB<float>::Green>);
  STATIC_CHECK(not std::same_as<SRGB<float>::Red, SRGB<float>::Blue>);

  // red in sRGB space is not the same as red in linear RGB space
  STATIC_CHECK(not std::same_as<SRGB<float>::Red, LinearRGB<float>::Red>);

  STATIC_CHECK(not std::same_as<SRGB<float>, SRGB<double>>);
}
