#include <ratio.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

//! @NOTE Some of the equality checks have additional parens; gcc wouldn't compile without them.

TEST_CASE("`Ratio`") {
  STATIC_CHECK(Ratio{ 1, 1 } == 1.0);
  STATIC_CHECK(Ratio{ 1, 2 } == .5);
  STATIC_CHECK(Ratio{ 2, 2 } == 1.0);
  STATIC_CHECK(Ratio{ 2, 1 } == 2.0);
}

template<typename R>
struct S {
  using type = R;
};

template<auto R>
struct T {
  static constexpr auto value = R;
};

template<Ratio R>
struct U {
  static constexpr auto value = R;
};

TEST_CASE("`Ratio`: Template parameter") {
  STATIC_CHECK(T<Ratio{1, 1}>::value == 1.0);

  STATIC_CHECK(U<Ratio{1, 1}>::value == 1.0);
}

TEST_CASE("`Ratio`: Comparison") {
  const auto N = GENERATE(2ULL, 3ULL);
  const auto D = GENERATE(2ULL, 3ULL);

  SECTION("Equality") {
    const Ratio X { N, D };
    const Ratio Y { N, D };

    CAPTURE(X, Y);

    CHECK((X == Y));
    CHECK(X <= Y);
    CHECK(X >= Y);
  }

  SECTION("Less") {
    const Ratio Y { N, D };

    CAPTURE(Y);

    SECTION("By numerator") {
      const Ratio X { N - 1, D };

      CAPTURE(X);

      CHECK((X != Y));
      CHECK(X < Y);
      CHECK(X <= Y);
    }

    SECTION("By denominator") {
      const Ratio X { N, D + 1 };

      CAPTURE(X);

      CHECK((X != Y));
      CHECK(X < Y);
      CHECK(X <= Y);
    }
  }

  SECTION("Greater") {
    const Ratio Y { N, D };

    CAPTURE(Y);

    SECTION("By numerator") {
      const Ratio X { N + 1, D };

      CAPTURE(X);

      CHECK((X != Y));
      CHECK(X > Y);
      CHECK(X >= Y);
    }

    SECTION("By denominator") {
      const Ratio X { N, D - 1 };

      CAPTURE(X);

      CHECK((X != Y));
      CHECK(X > Y);
      CHECK(X >= Y);
    }
  }
}

TEST_CASE("`Ratio`: Divide by zero") {
}
