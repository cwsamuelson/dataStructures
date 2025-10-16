#include <colors/rgb.hh>
#include <colors/rgba.hh>
#include <colors/hsl.hh>
#include <colors/hsv.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

TEST_CASE("RGB") {
  Colors::RGB rgb;
  rgb.red;
  rgb.green;
  rgb.blue;
  rgb.r;
  rgb.g;
  rgb.b;
  rgb.v;
  rgb.value;
  rgb.bytes[0];
}

TEST_CASE("RGBA") {
  Colors::RGBA rgba;
  rgba.red;
  rgba.green;
  rgba.blue;
  rgba.alpha;
  rgba.r;
  rgba.g;
  rgba.b;
  rgba.a;
  rgba.value;
  rgba.bytes[0];
}

TEST_CASE("HSL") {
  Colors::HSL hsl;
  hsl.hue;
  hsl.saturation;
  hsl.luminance;
  hsl.h;
  hsl.s;
  hsl.l;
  hsv.value;
  hsl.bytes[0];
}

TEST_CASE("HSV") {
  Colors::HSV hsv;
  hsv.hue;
  hsv.saturation;
  hsv.value;
  hsv.h;
  hsv.s;
  hsv.v
  hsv.value; // redundant
  hsv.bytes[0];
}
