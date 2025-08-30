#include <polynomial-2d.hh>

#include <catch2/catch_all.hpp>

#include <random>

using namespace flp;
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

TEST_CASE("`Polynomial2D`") {
  std::mt19937 generator(Catch::rngSeed());
  std::uniform_real_distribution<float> distribution(0.f, 1000000000.f);

  SECTION("`evaluate`") {
    SECTION("constant") {
      SECTION("zero") {
        const Polynomial2D<float> polynomial(0);

        CHECK(polynomial.order() == 0);
        CHECK(polynomial[0] == 0);

        for (size_t i{}; i < 10; ++i) {
          const auto input = distribution(generator);
          CAPTURE(input, i);
          CHECK(polynomial(input) == 0.f);
        }
      }

      SECTION("Random value") {
        const auto value = distribution(generator);
        const Polynomial2D<float> polynomial(value);

        CHECK(polynomial.order() == 0);
        CHECK(polynomial[0] == value);

        for (size_t i{}; i < 10; ++i) {
          const auto input = distribution(generator);
          CAPTURE(input, i);
          CHECK(polynomial(input) == value);
        }
      }
    }

    SECTION("linear") {
      SECTION("zero") {
        const Polynomial2D<float> polynomial{ 0.f, 0.f };

        CHECK(polynomial.order() == 0);
        CHECK(polynomial[0] == 0.f);
        CHECK(polynomial[1] == 0.f);

        for (size_t i{}; i < 10; ++i) {
          const auto input = distribution(generator);
          CAPTURE(input, i);
          CHECK(polynomial(input) == 0.f);
        }
      }

      SECTION("linear only") {
        const Polynomial2D<float> polynomial{ 0.f, 1.f };

        CHECK(polynomial.order() == 1);
        CHECK(polynomial[0] == 0.f);
        CHECK(polynomial[1] == 1.f);

        for (size_t i{}; i < 10; ++i) {
          const auto input = distribution(generator);
          CAPTURE(input, i);
          CHECK(polynomial(input) == input);
        }
      }

      SECTION("1s") {
        const Polynomial2D<float> polynomial{ 1.f, 1.f };

        CHECK(polynomial.order() == 1);
        CHECK(polynomial[0] == 1.f);
        CHECK(polynomial[1] == 1.f);

        for (size_t i{}; i < 10; ++i) {
          const auto input = distribution(generator);
          CAPTURE(input, i);
          CHECK(polynomial(input) == input + 1);
        }
      }

      SECTION("Random coefficients") {
        const auto constant = distribution(generator);
        const auto linear = distribution(generator);
        const Polynomial2D<float> polynomial{ constant, linear };

        CAPTURE(constant, linear);

        CHECK(polynomial.order() == 1);
        CHECK(polynomial[0] == constant);
        CHECK(polynomial[1] == linear);

        for (size_t i{}; i < 10; ++i) {
          const auto input = distribution(generator);
          CAPTURE(input, i);
          CHECK(polynomial(input) == (input * linear + constant));
        }
      }
    }

    SECTION("quadratic") {
      SECTION("zero") {
        const Polynomial2D<float> polynomial{ 0.f, 0.f, 0.f };

        CHECK(polynomial.order() == 0);
        CHECK(polynomial[0] == 0.f);
        CHECK(polynomial[1] == 0.f);
        CHECK(polynomial[2] == 0.f);

        for (size_t i{}; i < 10; ++i) {
          const auto input = distribution(generator);
          CAPTURE(input, i);
          CHECK(polynomial(input) == 0.f);
        }
      }

      SECTION("quad only") {
        const Polynomial2D<float> polynomial{ 0.f, 0.f, 1.f };

        CHECK(polynomial.order() == 2);
        CHECK(polynomial[0] == 0.f);
        CHECK(polynomial[1] == 0.f);
        CHECK(polynomial[2] == 1.f);

        for (size_t i{}; i < 10; ++i) {
          const auto input = distribution(generator);
          const auto expected = input * input;

          CAPTURE(input, i);
          CHECK_THAT(polynomial(input),
                     WithinRel(expected, 0.001) or WithinAbs(expected, 0.000001));
        }
      }

      SECTION("Random coefficients") {
        const auto constant = distribution(generator);
        const auto linear = distribution(generator);
        const auto quadratic = distribution(generator);
        const Polynomial2D<float> polynomial{ constant, linear, quadratic };

        CAPTURE(constant, linear, quadratic);

        CHECK(polynomial.order() == 2);
        CHECK(polynomial[0] == constant);
        CHECK(polynomial[1] == linear);
        CHECK(polynomial[2] == quadratic);

        for (size_t i{}; i < 10; ++i) {
          const auto input = distribution(generator);
          const auto expected = (input * input * quadratic) +  (input * linear) + constant;

          CAPTURE(input, i);
          CHECK_THAT(polynomial(input),
                     WithinRel(expected, 0.001) or WithinAbs(expected, 0.000001));
        }
      }
    }
  }

  SECTION("`solve`") {
    SECTION("constant") {
      SECTION("zero") {
        const Polynomial2D<float> polynomial(0);

        const auto roots = polynomial.solve();

        CHECK(roots.empty());
      }

      SECTION("Random value") {
        const auto value = distribution(generator);
        const Polynomial2D<float> polynomial(value);

        CHECK(polynomial.order() == 0);
        CHECK(polynomial[0] == value);

        const auto roots = polynomial.solve();

        CHECK(roots.empty());
      }
    }

    SECTION("linear") {
      SECTION("zero") {
        const Polynomial2D<float> polynomial{ 0.f, 0.f };

        CHECK(polynomial.order() == 0);
        CHECK(polynomial[0] == 0.f);
        CHECK(polynomial[1] == 0.f);

        const auto roots = polynomial.solve();
      }

      SECTION("linear only") {
        const Polynomial2D<float> polynomial{ 0.f, 1.f };

        CHECK(polynomial.order() == 1);
        CHECK(polynomial[0] == 0.f);
        CHECK(polynomial[1] == 1.f);

        const auto roots = polynomial.solve();
      }

      SECTION("1s") {
        const Polynomial2D<float> polynomial{ 1.f, 1.f };

        CHECK(polynomial.order() == 1);
        CHECK(polynomial[0] == 1.f);
        CHECK(polynomial[1] == 1.f);

        const auto roots = polynomial.solve();
      }

      SECTION("Random coefficients") {
        const auto constant = distribution(generator);
        const auto linear = distribution(generator);
        const Polynomial2D<float> polynomial{ constant, linear };

        CAPTURE(constant, linear);

        CHECK(polynomial.order() == 1);
        CHECK(polynomial[0] == constant);
        CHECK(polynomial[1] == linear);

        const auto roots = polynomial.solve();
      }
    }

    SECTION("quadratic") {
      SECTION("zero") {
        const Polynomial2D<float> polynomial{ 0.f, 0.f, 0.f };

        CHECK(polynomial.order() == 0);
        CHECK(polynomial[0] == 0.f);
        CHECK(polynomial[1] == 0.f);
        CHECK(polynomial[2] == 0.f);

        const auto roots = polynomial.solve();
      }

      SECTION("quad only") {
        const Polynomial2D<float> polynomial{ 0.f, 0.f, 1.f };

        CHECK(polynomial.order() == 2);
        CHECK(polynomial[0] == 0.f);
        CHECK(polynomial[1] == 0.f);
        CHECK(polynomial[2] == 1.f);

        const auto roots = polynomial.solve();
      }

      SECTION("Random coefficients") {
        const auto constant = distribution(generator);
        const auto linear = distribution(generator);
        const auto quadratic = distribution(generator);
        const Polynomial2D<float> polynomial{ constant, linear, quadratic };

        CAPTURE(constant, linear, quadratic);

        CHECK(polynomial.order() == 2);
        CHECK(polynomial[0] == constant);
        CHECK(polynomial[1] == linear);
        CHECK(polynomial[2] == quadratic);

        const auto roots = polynomial.solve();
      }
    }
  }

  SECTION("calculus") {
    SECTION("`derive`") {
      SECTION("constant") {
        const auto value = distribution(generator);
        const Polynomial2D<float> polynomial{ value };

        CAPTURE(value);
        CHECK(polynomial.derive() == Polynomial2D<float>{});
      }

      SECTION("linear") {
        const auto constant = distribution(generator);
        const auto linear = distribution(generator);
        const Polynomial2D<float> polynomial{ constant, linear };

        CAPTURE(constant, linear);
        CHECK(polynomial.derive() == Polynomial2D<float>{ linear });
      }
    }

    SECTION("`antiderive`") {
    }

    SECTION("`integrate`") {
    }
  }

  SECTION("copy") {
    const auto constant = distribution(generator);
    const auto linear = distribution(generator);
    const auto quadratic = distribution(generator);
    const Polynomial2D<float> poly1{ constant, linear, quadratic };

    SECTION("ctor") {
      const Polynomial2D<float> poly2(poly1);

      CHECK(poly1 == poly2);
    }

    SECTION("operator") {
      SECTION("elided") {
        const Polynomial2D<float> poly2 = poly1;

        CHECK(poly1 == poly2);
      }

      SECTION("mutable") {
        Polynomial2D<float> poly2;

        CHECK(poly1 != poly2);

        poly2 = poly1;

        CHECK(poly1 == poly2);
      }
    }
  }

  // auto operator<=>(const Polynomial2D&, const Polynomial2D&) noexcept = default;
  // Polynomial2D operator*(const Polynomial2D& lhs, const Polynomial2D& rhs) noexcept;
  // Polynomial2D operator/(const Polynomial2D& lhs, const Polynomial2D& rhs) noexcept;
}
