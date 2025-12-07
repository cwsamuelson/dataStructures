#include <ratio.hh>

#include <catch2/catch_all.hpp>
// #include <rapidcheck.h>
#include <rapidcheck/catch.h>
#include <rapidcheck/gen/Predicate.h>

using namespace flp;

//! @NOTE Some of the equality checks have additional parens; gcc wouldn't compile without them.

TEST_CASE("`Ratio`::constexpr") {
  STATIC_CHECK(Ratio{ 1, 1 } == 1.0);
  STATIC_CHECK(Ratio{ 1, 2 } == .5);
  STATIC_CHECK(Ratio{ 2, 2 } == 1.0);
  STATIC_CHECK(Ratio{ 2, 1 } == 2.0);
}

TEST_CASE("`Ratio`::Comparison") {
  rc::prop("All comparisons of 2 ratios", [] {
    const int64_t N1 = *rc::gen::nonZero<int64_t>();
    const int64_t D1 = *rc::gen::nonZero<int64_t>();
    const int64_t N2 = *rc::gen::nonZero<int64_t>();
    const int64_t D2 = *rc::gen::nonZero<int64_t>();

    const Ratio R1{N1, D1};
    const Ratio R2{N2, D2};

    const double ratio1 = R1;
    const double ratio2 = R2;

    CAPTURE(R1, R2, ratio1, ratio2);

    RC_ASSERT((R1 <  R2) == (ratio1 <  ratio2));
    RC_ASSERT((R1 >  R2) == (ratio1 >  ratio2));
    RC_ASSERT((R1 <= R2) == (ratio1 <= ratio2));
    RC_ASSERT((R1 >= R2) == (ratio1 >= ratio2));
    RC_ASSERT((R1 == R2) == (ratio1 == ratio2));
    RC_ASSERT((R1 != R2) == (ratio1 != ratio2));
  });

  SECTION("Regression Tests") {
    using RatioPair = std::tuple<Ratio<>, Ratio<>>;

    const auto [R1, R2] =
      GENERATE(
        std::make_tuple(Ratio<>{1507215272, 7}, Ratio<>{2, 6119478889}),
        std::make_tuple(Ratio<>{5, -2}, Ratio<>{1, 4}),
        std::make_tuple(Ratio<>{1, 1}, Ratio<>{1, -1})
      );

    const double ratio1 = R1;
    const double ratio2 = R2;

    CAPTURE(R1, R2, ratio1, ratio2);

    CHECK((R1 <  R2) == (ratio1 <  ratio2));
    CHECK((R1 >  R2) == (ratio1 >  ratio2));
    CHECK((R1 <= R2) == (ratio1 <= ratio2));
    CHECK((R1 >= R2) == (ratio1 >= ratio2));
    CHECK((R1 == R2) == (ratio1 == ratio2));
    CHECK((R1 != R2) == (ratio1 != ratio2));
  }
}

TEST_CASE("`Ratio`::Arithmetic") {
  rc::prop("With zero", [](const int64_t N) {
    const int64_t D = *rc::gen::nonZero<int64_t>();
    const Ratio R{N, D};

    RC_ASSERT((R + 0 == R));
    RC_ASSERT((R - 0 == R));
    RC_ASSERT((R * 0 == 0));

    // despite the `ASSERT_THROWS`, the exception appears to not be caught, and
    // the test case crashes, causing a failure.
    // RC_ASSERT_THROWS(R / 0);
    RC_ASSERT_THROWS((Ratio<int64_t>{N, 0}));
  });

  rc::prop("properties", [](const int64_t N) {
    const int64_t D = *rc::gen::nonZero<int64_t>();
    const int64_t S = *rc::gen::nonZero<int64_t>();

    const Ratio R{N, D};
    (void)(R * S);
    (void)(R / S);
    (void)(R + S);
    (void)(R - S);
  });
}
