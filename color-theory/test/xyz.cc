#include <color_theory/xyz.hh>

#include <catch2/catch_all.hpp>

using namespace flp::ColorTheory;

TEST_CASE("Color Theory: XYZ construction and comparison") {
  const XYZ<float> value{
    XYZ<float>::X(0.1f),
    XYZ<float>::Y(0.2f),
    XYZ<float>::Z(0.3f),
  };

  CHECK(value.x() == 0.1f);
  CHECK(value.y() == 0.2f);
  CHECK(value.z() == 0.3f);
  CHECK(value != XYZ<float>{});

  CHECK(value == XYZ<float>::X(0.1f));
  CHECK(static_cast<XYZ<float>::X>(value) == 0.1f);
}

TEST_CASE("Color Theory: XYZ channels are distinct types") {
  STATIC_CHECK(not std::same_as<XYZ<float>::X, XYZ<float>::Y>);
  STATIC_CHECK(not std::same_as<XYZ<float>::Y, XYZ<float>::Z>);
  STATIC_CHECK(not std::same_as<XYZ<float>::Z, XYZ<float>::X>);
}
