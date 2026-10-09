#include <color_theory/rgb.hh>
#include <color_theory/rgba.hh>
#include <color_theory/hsl.hh>
#include <color_theory/hsv.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

TEST_CASE("RGB") {
  ColorTheory::RGB8 rgb(10, 21, 32);
  CHECK(rgb.red() == 10);
  CHECK(rgb.green() == 21);
  CHECK(rgb.blue() == 32);

  CHECK(rgb.r() == 10);
  CHECK(rgb.g() == 21);
  CHECK(rgb.b() == 32);

  // CHECK(rgb.bit_value<uint32_t>() == 0x0A1520);
  // CHECK(rgb.bytes[0] == 10);
  // CHECK(rgb.bytes[1] == 21);
  // CHECK(rgb.bytes[2] == 32);

  CHECK(&rgb.red() == &rgb.r());
  CHECK(&rgb.green() == &rgb.g());
  CHECK(&rgb.blue() == &rgb.b());
}

TEST_CASE("RGBA") {
  ColorTheory::RGBA8 rgba(10, 21, 32, 255);
  CHECK(rgba.red() == 10);
  CHECK(rgba.green() == 21);
  CHECK(rgba.blue() == 32);
  CHECK(rgba.alpha() == 255);
  CHECK(rgba.r() == 10);
  CHECK(rgba.g() == 21);
  CHECK(rgba.b() == 32);
  CHECK(rgba.a() == 255);
  // CHECK(rgba.bit_value<uint32_t>() == 0x0A1520FF);
  // CHECK(rgba.bytes()[0] == 10);
  // CHECK(rgba.bytes()[1] == 21);
  // CHECK(rgba.bytes()[2] == 32);
  // CHECK(rgba.bytes()[3] == 255);
}

TEST_CASE("HSL") {
  ColorTheory::HSL<int> hsl(10, 21, 32);
  CHECK(hsl.hue() == 10);
  CHECK(hsl.saturation() == 21);
  CHECK(hsl.lightness() == 32);
  CHECK(hsl.h() == 10);
  CHECK(hsl.s() == 21);
  CHECK(hsl.l() == 32);
  // hsl.value;
  // hsl.bytes[0];
}

TEST_CASE("HSV") {
  ColorTheory::HSV<int> hsv(10, 21, 32);
  CHECK(hsv.hue() == 10);
  CHECK(hsv.saturation() == 21);
  // CHECK(hsv.bit_value<uint32_t>() == 32);
  CHECK(hsv.h() == 10);
  CHECK(hsv.s() == 21);
  CHECK(hsv.v() == 32);
  // CHECK(hsv.value; // redundant
  // CHECK(hsv.bytes[0];
}
