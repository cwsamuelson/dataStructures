#include <ratio.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

TEST_CASE("Ratio") {
  SECTION("As value") {
    STATIC_CHECK(RatioValue{ 1, 1 } == 1.0);
    STATIC_CHECK(RatioValue{ 1, 2 } == .5);
    STATIC_CHECK(RatioValue{ 2, 2 } == 1.0);
    STATIC_CHECK(RatioValue{ 2, 1 } == 2.0);
  }

  SECTION("As type") {
    STATIC_CHECK(RatioType<1, 1>{} == 1.0);
    STATIC_CHECK(RatioType<1, 2>{} == .5);
    STATIC_CHECK(RatioType<2, 2>{} == 1.0);
    STATIC_CHECK(RatioType<2, 1>{} == 2.0);
  }
}

template<typename R>
struct S {
  using type = R;
};

template<auto R>
struct T {
  static constexpr auto value = R;
};

template<RatioValue R>
struct U {
  static constexpr auto value = R;
};

TEST_CASE("Template parameter") {
  STATIC_CHECK(S<RatioType<1, 1>>::type{} == 1.0);

  STATIC_CHECK(T<RatioValue{1, 1}>::value == 1.0);

  STATIC_CHECK(U<RatioValue{1, 1}>::value == 1.0);
}

TEST_CASE("Comparison") {
  const auto N = GENERATE(1ULL, 2ULL);
  const auto D = GENERATE(1ULL, 2ULL);

  SECTION("Equality") {
    const RatioValue X { N, D };
    const RatioValue Y { N, D };
    CHECK(X == Y);
    CHECK(X <= Y);
    CHECK(X >= Y);
  }

  SECTION("Less") {
    const RatioValue Y { N, D };

    SECTION("By numerator") {
      const RatioValue X { N - 1, D };

      CHECK(X != Y);
      CHECK(X < Y);
      CHECK(X <= Y);
    }

    SECTION("By denominator") {
      const RatioValue X { N, D + 1 };

      CHECK(X != Y);
      CHECK(X < Y);
      CHECK(X <= Y);
    }
  }

  SECTION("More") {
    const RatioValue Y { N, D };

    SECTION("By numerator") {
      const RatioValue X { N + 1, D };

      CHECK(X != Y);
      CHECK(X > Y);
      CHECK(X >= Y);
    }

    SECTION("By denominator") {
      const RatioValue X { N, D - 1 };

      CHECK(X != Y);
      CHECK(X > Y);
      CHECK(X >= Y);
    }
  }
}

TEST_CASE("Divide by zero") {
}

