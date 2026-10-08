#include <color_theory/cmyk.hh>

#include <catch2/catch_all.hpp>

using namespace flp::ColorTheory;

TEST_CASE("Color Theory: CMYK construction and comparison") {
  const CMYK<float> value {
    CMYK<float>::Cyan(0.1f),
    CMYK<float>::Magenta(0.2f),
    CMYK<float>::Yellow(0.3f),
    CMYK<float>::Key(0.4f),
  };

  CHECK(value.cyan()    == 0.1f);
  CHECK(value.magenta() == 0.2f);
  CHECK(value.yellow()  == 0.3f);
  CHECK(value.key()     == 0.4f);
  CHECK(value != CMYK<float>{});

  CHECK(value == CMYK<float>::Cyan(0.1f));
  CHECK(static_cast<CMYK<float>::Cyan>(value) == 0.1f);
}

TEST_CASE("Color Theory: CMYK channels are distinct types") {
  STATIC_CHECK(not std::same_as<CMYK<float>::Cyan, CMYK<float>::Magenta>);
  STATIC_CHECK(not std::same_as<CMYK<float>::Magenta, CMYK<float>::Yellow>);
  STATIC_CHECK(not std::same_as<CMYK<float>::Yellow, CMYK<float>::Key>);
}
