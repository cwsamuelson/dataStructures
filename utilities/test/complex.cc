#include <complex.hh>

#include <catch2/catch_all.hpp>
#include <rapidcheck/catch.h>
#include <rapidcheck/gen/Predicate.h>

using namespace flp;

TEST_CASE("`Complex`") {
  rc::prop("Initialization", [](const float r, const float i) {
    const Complex<float> value{r, i};

    RC_ASSERT(value.r() == r);
    RC_ASSERT(value.i() == i);
    RC_ASSERT(value.conjugate() == (Complex<float>{r, -i}));
  });

  rc::prop("Math", [](const float r0, const float i0, const float r1, const float i1) {
    const Complex<float> value0{r0, i0};
    const Complex<float> value1{r1, i1};

    RC_ASSERT(value0 + value1 == (Complex<float>{r0 + r1, i0 + i1}));
    RC_ASSERT(value0 - value1 == (Complex<float>{r0 - r1, i0 - i1}));
    // RC_ASSERT(value0 * value1 == (Complex<float>{r0 ? r1, i0 ? i1}));
    // RC_ASSERT(value0 / value1 == (Complex<float>{r0 ? r1, i0 ? i1}));
  });

  SECTION("Golden math") {
    SECTION("0") {
      const Complex<float> value0{-3.f, -5.f};
      const Complex<float> value1{0.f, 2.f};

      // CHECK(value0 * value1 == (Complex<float>{r0 ? r1, i0 ? i1}));
      CHECK(value0 / value1 == (Complex<float>{-5.f / 2.f, 3.f / 2.f}));
    }

    SECTION("1") {
      const Complex<float> value0{-1.f, 0.f};
      const Complex<float> value1{3.f, 2.f};

      // CHECK(value0 * value1 == (Complex<float>{r0 ? r1, i0 ? i1}));
      CHECK(value0 / value1 == (Complex<float>{-3.f / 13.f, 2.f / 13.f}));
    }

    SECTION("2") {
      const Complex<float> value0{1.f, 0.f};
      const Complex<float> value1{3.f, 2.f};

      // CHECK(value0 * value1 == (Complex<float>{r0 ? r1, i0 ? i1}));
      CHECK(value0 / value1 == (Complex<float>{3.f / 13.f, -2.f / 13.f}));
    }

    SECTION("3") {
      const Complex<float> value0{5.f, std::sqrt(2.f)};
      const Complex<float> value1{1.f, -std::sqrt(2.f)};

      // CHECK(value0 * value1 == (Complex<float>{r0 ? r1, i0 ? i1}));
      CHECK(value0 / value1 == (Complex<float>{1.f, 2 * std::sqrt(2.f)}));
    }
  }

  rc::prop("Math with 'normal' numbers", [](const float r, const float i, const float f) {
    const Complex<float> value{r, i};

    RC_ASSERT(value + f == (Complex<float>{r + f, i}));
    RC_ASSERT(f + value == (Complex<float>{f + r, i}));
    RC_ASSERT(value - f == (Complex<float>{r - f, i}));
    RC_ASSERT(f - value == (Complex<float>{f - r, i}));

    RC_ASSERT(value * f == (Complex<float>{r * f, i * f}));
    RC_ASSERT(f * value == (Complex<float>{f * r, f * i}));
    RC_ASSERT(value / f == (Complex<float>{r / f, i / f}));
    RC_ASSERT(f / value == (Complex<float>{f / r, f / i}));
  });

  rc::prop("Magnitude", [](const float f) {
    const Complex<float> value_r{f, 0.f};
    const Complex<float> value_i{0.f, f};

    RC_ASSERT(value_r.magnitude() == std::abs(f));
    RC_ASSERT(value_i.magnitude() == std::abs(f));
  });
}
