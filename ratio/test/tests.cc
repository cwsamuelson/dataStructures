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

  SECTION("Repro0") {
    const int64_t N1 = 1;
    const int64_t D1 = 1;
    const int64_t N2 = 1;
    const int64_t D2 = -1;

    const Ratio R1{N1, D1};
    const Ratio R2{N2, D2};

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

  SECTION("Repro1") {
    const int64_t N1 = 5;
    const int64_t D1 = -2;
    const int64_t N2 = 1;
    const int64_t D2 = 4;

    const Ratio R1{N1, D1};
    const Ratio R2{N2, D2};

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

  SECTION("Repro2") {
    std::println("@@@ Repro2 top");
    const int64_t N1 = 1507215272;
    const int64_t D1 = 7;
    const int64_t N2 = 2;
    const int64_t D2 = 6119478889;

    const Ratio R1{N1, D1};
    const Ratio R2{N2, D2};

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

TEST_CASE("`Ratio`: Divide by zero") {
  const auto numerator = GENERATE(0, 1, 2, 3, 4, 5, 100, 1000, 10000);
  CHECK_THROWS(Ratio{numerator, 0});
}
