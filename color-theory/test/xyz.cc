#include <color_theory/xyz/xyz.hh>

#include <catch2/catch_all.hpp>

using namespace flp::ColorTheory;

TEST_CASE("Color Theory: XYZ construction and comparison") {
  const XYZ<float> value{
    XYZ<float>::X(0.1f),
    XYZ<float>::Y(0.2f),
    XYZ<float>::Z(0.3f),
  };

  CHECK(value.x == XYZ<float>::X(0.1f));
  CHECK(value.y == XYZ<float>::Y(0.2f));
  CHECK(value.z == XYZ<float>::Z(0.3f));
  CHECK(value != XYZ<float>{});
}

TEST_CASE("Color Theory: XYZ channels are distinct types") {
  STATIC_CHECK(not std::same_as<XYZ<float>::X, XYZ<float>::Y>);
  STATIC_CHECK(not std::same_as<XYZ<float>::Y, XYZ<float>::Z>);
  STATIC_CHECK(not std::same_as<XYZ<float>::X, XYZ<float>::Z>);
}
