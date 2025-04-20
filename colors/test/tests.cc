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
  rgb.value;
}

TEST_CASE("RGBA") {
  Colors::RGBA rgba;
  rgba.red;
  rgba.green;
  rgba.blue;
  rgba.alpha;
  rgba.value;
}

TEST_CASE("HSL") {
}

TEST_CASE("HSV") {
}

