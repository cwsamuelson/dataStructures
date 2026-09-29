#include <color_theory/color_theory.hh>

#include <catch2/catch_all.hpp>

using namespace flp::ColorTheory;
using Catch::Matchers::WithinAbs;
using Catch::Matchers::WithinRel;

static constexpr float epsilon = 1e-4;

TEST_CASE("Color Theory: convert: identity is a no-op") {
  const SRGB<float> value{
    SRGB<float>::Red(0.3f),
    SRGB<float>::Green(0.6f),
    SRGB<float>::Blue(0.9f),
  };
  CHECK(convert<SRGB<float>>(value) == value);
}

TEST_CASE("Color Theory: convert: SRGB <-> LinearRGB round trip") {
  const SRGB<float> original{
    SRGB<float>::Red(0.75f),
    SRGB<float>::Green(0.25f),
    SRGB<float>::Blue(0.5f),
  };

  const auto linear   = convert<LinearRGB<float>>(original);
  const auto roundtrip = convert<SRGB<float>>(linear);

  CHECK_THAT(float(roundtrip.red), WithinRel(float(original.red), .1));
  CHECK_THAT(float(roundtrip.green), WithinRel(float(original.green), .1));
  CHECK_THAT(float(roundtrip.blue), WithinRel(float(original.blue), .1));
}

TEST_CASE("Color Theory: convert: LinearRGB <-> XYZ round trip") {
  const LinearRGB<float> original{
    LinearRGB<float>::Red(0.2f),
    LinearRGB<float>::Green(0.4f),
    LinearRGB<float>::Blue(0.6f),
  };

  const auto xyz       = convert<XYZ<float>>(original);
  const auto roundtrip = convert<LinearRGB<float>>(xyz);

  CHECK_THAT(float(roundtrip.red), WithinRel(float(original.red), .1));
  CHECK_THAT(float(roundtrip.green), WithinRel(float(original.green), .1));
  CHECK_THAT(float(roundtrip.blue), WithinRel(float(original.blue), .1));
}

TEST_CASE("Color Theory: convert: XYZ <-> Lab round trip") {
  const XYZ<float> original{
    XYZ<float>::X(0.3f),
    XYZ<float>::Y(0.5f),
    XYZ<float>::Z(0.2f),
  };

  const auto lab        = convert<Lab<float>>(original);
  const auto roundtrip  = convert<XYZ<float>>(lab);

  CHECK_THAT(float(roundtrip.x), WithinRel(float(original.x), .1));
  CHECK_THAT(float(roundtrip.y), WithinRel(float(original.y), .1));
  CHECK_THAT(float(roundtrip.z), WithinRel(float(original.z), .1));
}

TEST_CASE("Color Theory: convert: SRGB <-> HSV round trip") {
  const SRGB<float> original{
    SRGB<float>::Red(.1f),
    SRGB<float>::Green(0.8f),
    SRGB<float>::Blue(0.3f),
  };

  const auto hsv        = convert<HSV<float>>(original);
  const auto roundtrip  = convert<SRGB<float>>(hsv);

  CHECK_THAT(float(roundtrip.red), WithinRel(float(original.red), .1));
  CHECK_THAT(float(roundtrip.green), WithinRel(float(original.green), .1));
  CHECK_THAT(float(roundtrip.blue), WithinRel(float(original.blue), .1));
}

TEST_CASE("Color Theory: convert: SRGB <-> HSL round trip") {
  const SRGB<float> original{
    SRGB<float>::Red(0.9f),
    SRGB<float>::Green(0.2f),
    SRGB<float>::Blue(0.4f),
  };

  const auto hsl        = convert<HSL<float>>(original);
  const auto roundtrip  = convert<SRGB<float>>(hsl);

  CHECK_THAT(float(roundtrip.red), WithinRel(float(original.red), .1));
  CHECK_THAT(float(roundtrip.green), WithinRel(float(original.green), .1));
  CHECK_THAT(float(roundtrip.blue), WithinRel(float(original.blue), .1));
}

TEST_CASE("Color Theory: convert: SRGB <-> CMYK round trip") {
  const SRGB<float> original{
    SRGB<float>::Red(0.6f),
    SRGB<float>::Green(0.6f),
    SRGB<float>::Blue(.1f),
  };

  const auto cmyk       = convert<CMYK<float>>(original);
  const auto roundtrip  = convert<SRGB<float>>(cmyk);

  CHECK_THAT(float(roundtrip.red), WithinRel(float(original.red), .1));
  CHECK_THAT(float(roundtrip.green), WithinRel(float(original.green), .1));
  CHECK_THAT(float(roundtrip.blue), WithinRel(float(original.blue), .1));
}

TEST_CASE("Color Theory: convert: multi-hop HSV <-> Lab round trip (HSV -> SRGB -> LinearRGB -> XYZ -> Lab)") {
  const HSV<float> original{
    HSV<float>::Hue(210.f),
    HSV<float>::Saturation(0.6f),
    HSV<float>::Value(0.7f),
  };

  const auto lab        = convert<Lab<float>>(original);
  const auto roundtrip  = convert<HSV<float>>(lab);

  CHECK_THAT(float(roundtrip.hue), WithinRel(float(original.hue), .1));
  CHECK_THAT(float(roundtrip.saturation), WithinRel(float(original.saturation), .1));
  CHECK_THAT(float(roundtrip.value), WithinRel(float(original.value), .1));
}

TEST_CASE("Color Theory: convert: sibling-to-sibling CMYK <-> HSL (via shared SRGB parent, no direct edge)") {
  // CMYK has more more parameters than other color spaces (srgb, hsl in this case)
  // This means that many CMYK values may map to a single RGB value.  For round
  // trip conversion to function, the CMYK value must satisfy the K = 1 - max(r,g,b)
  // relationship.  A cheap way to ensure that here is to use our own sRGB type

  const SRGB<float> source{
    SRGB<float>::Red(0.56f),
    SRGB<float>::Green(0.35f),
    SRGB<float>::Blue(0.63f),
  };
  const auto original = convert<CMYK<float>>(source);

  const auto hsl        = convert<HSL<float>>(original);
  const auto roundtrip  = convert<CMYK<float>>(hsl);

  CHECK_THAT(float(roundtrip.cyan), WithinRel(float(original.cyan), .1));
  CHECK_THAT(float(roundtrip.magenta), WithinRel(float(original.magenta), .1));
  CHECK_THAT(float(roundtrip.yellow), WithinRel(float(original.yellow), .1));
  CHECK_THAT(float(roundtrip.key), WithinRel(float(original.key), .1));
}

TEST_CASE("Color Theory: convert: known values - white") {
  const SRGB<float> white{
    SRGB<float>::Red(1.f),
    SRGB<float>::Green(1.f),
    SRGB<float>::Blue(1.f),
  };

  // D65 white point: X=0.95047, Y=1.0, Z=1.08883.
  const auto xyz = convert<XYZ<float>>(white);
  CHECK_THAT(float(xyz.x), WithinRel(0.95047f, .1f));
  CHECK_THAT(float(xyz.y), WithinRel(1.0f, .1f));
  CHECK_THAT(float(xyz.z), WithinRel(1.08883f, .1f));

  const auto lab = convert<Lab<float>>(white);
  CHECK_THAT(float(lab.l), WithinRel(100.0f, .1f));
  CHECK_THAT(float(lab.a), WithinAbs(0.0f, epsilon));
  CHECK_THAT(float(lab.b), WithinAbs(0.0f, epsilon));
}

TEST_CASE("Color Theory: convert: known values - black") {
  const SRGB<float> black{};

  const auto xyz = convert<XYZ<float>>(black);
  CHECK_THAT(float(xyz.x), WithinAbs(0.0f, epsilon));
  CHECK_THAT(float(xyz.y), WithinAbs(0.0f, epsilon));
  CHECK_THAT(float(xyz.z), WithinAbs(0.0f, epsilon));

  const auto lab = convert<Lab<float>>(black);
  CHECK_THAT(float(lab.l), WithinAbs(0.0f, epsilon));
}

TEST_CASE("Color Theory: convert: known values - pure red") {
  const SRGB<float> red {
    SRGB<float>::Red(1.f),
    SRGB<float>::Green(0.f),
    SRGB<float>::Blue(0.f),
  };

  const auto hsv = convert<HSV<float>>(red);
  CHECK_THAT(float(hsv.hue),        WithinAbs(0.0f, epsilon));
  CHECK_THAT(float(hsv.saturation), WithinRel(1.0f, .1f));
  CHECK_THAT(float(hsv.value),      WithinRel(1.0f, .1f));

  const auto cmyk = convert<CMYK<float>>(red);
  CHECK_THAT(float(cmyk.cyan),    WithinAbs(0.0f, epsilon));
  CHECK_THAT(float(cmyk.magenta), WithinRel(1.0f, .1f));
  CHECK_THAT(float(cmyk.yellow),  WithinRel(1.0f, .1f));
  CHECK_THAT(float(cmyk.key),     WithinAbs(0.0f, epsilon));
}
