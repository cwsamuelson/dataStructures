#include <polynomial-2d.hh>

#include <catch2/catch_all.hpp>
#include <rapidcheck/catch.h>
#include <rapidcheck/Gen.h>
#include <rapidcheck/gen/Numeric.h>

#include <random>

using namespace flp;
using Catch::Matchers::WithinRel;
using Catch::Matchers::WithinAbs;

// with rapidcheck, many of the special cases like 'zero' or 'linear only' are
// probably unnecessary.
// The only caveat to them is the `.order() == N` check, which is dependent on
// the 'zero-ness' of the coefficients.  While easy enough to fix, I don't feel
// like it for now.
TEST_CASE("`Polynomial2D`") {
  SECTION("`evaluate`") {
    SECTION("constant") {
      rc::prop("zero", [](const float input) {
        const Polynomial2D<float> polynomial(0);

        RC_ASSERT(polynomial.order() == 0);
        RC_ASSERT(polynomial[0] == 0);

        RC_ASSERT(polynomial(input) == 0.f);
      });

      rc::prop("Random value", [](const float value, const float input) {
        const Polynomial2D<float> polynomial(value);

        RC_ASSERT(polynomial.order() == 0);
        RC_ASSERT(polynomial[0] == value);

        RC_ASSERT(polynomial(input) == value);
      });
    }

    SECTION("linear") {
      rc::prop("zero", [](const float input) {
        const Polynomial2D<float> polynomial{ 0.f, 0.f };

        RC_ASSERT(polynomial.order() == 0);
        RC_ASSERT(polynomial[0] == 0.f);
        RC_ASSERT(polynomial[1] == 0.f);

        RC_ASSERT(polynomial(input) == 0.f);
      });

      rc::prop("linear only", [](const float input) {
        const Polynomial2D<float> polynomial{ 0.f, 1.f };

        RC_ASSERT(polynomial.order() == 1);
        RC_ASSERT(polynomial[0] == 0.f);
        RC_ASSERT(polynomial[1] == 1.f);

        RC_ASSERT(polynomial(input) == input);
      });

      rc::prop("1s", [](const float input) {
        const Polynomial2D<float> polynomial{ 1.f, 1.f };

        RC_ASSERT(polynomial.order() == 1);
        RC_ASSERT(polynomial[0] == 1.f);
        RC_ASSERT(polynomial[1] == 1.f);

        RC_ASSERT(polynomial(input) == input + 1);
      });

      rc::prop("Random coefficients", [](const float constant, const float input) {
        const auto linear = *rc::gen::nonZero<float>();
        const Polynomial2D<float> polynomial{ constant, linear };

        CAPTURE(constant, linear);

        RC_ASSERT(polynomial.order() == 1);
        RC_ASSERT(polynomial[0] == constant);
        RC_ASSERT(polynomial[1] == linear);

        RC_ASSERT(polynomial(input) == (input * linear + constant));
      });
    }

    SECTION("quadratic") {
      rc::prop("zero", [](const float input) {
        const Polynomial2D<float> polynomial{ 0.f, 0.f, 0.f };

        RC_ASSERT(polynomial.order() == 0);
        RC_ASSERT(polynomial[0] == 0.f);
        RC_ASSERT(polynomial[1] == 0.f);
        RC_ASSERT(polynomial[2] == 0.f);

        RC_ASSERT(polynomial(input) == 0.f);
      });

      rc::prop("quad only", [](const float input) {
        const Polynomial2D<float> polynomial{ 0.f, 0.f, 1.f };

        RC_ASSERT(polynomial.order() == 2);
        RC_ASSERT(polynomial[0] == 0.f);
        RC_ASSERT(polynomial[1] == 0.f);
        RC_ASSERT(polynomial[2] == 1.f);

        const auto expected = input * input;
        // no RC_ equivalent ...
        CHECK_THAT(polynomial(input),
                   WithinRel(expected, 0.001) or WithinAbs(expected, 0.000001));
      });

      rc::prop("Random coefficients", [](const float constant, const float input) {
        const auto linear = *rc::gen::nonZero<float>();
        const auto quadratic = *rc::gen::nonZero<float>();
        const Polynomial2D<float> polynomial{ constant, linear, quadratic };

        RC_ASSERT(polynomial.order() == 2);
        RC_ASSERT(polynomial[0] == constant);
        RC_ASSERT(polynomial[1] == linear);
        RC_ASSERT(polynomial[2] == quadratic);

        const auto expected = (input * input * quadratic) +  (input * linear) + constant;
        // no RC_ equivalent ...
        CHECK_THAT(polynomial(input),
                   WithinRel(expected, 0.001) or WithinAbs(expected, 0.000001));
      });
    }
  }

  SECTION("`solve`") {
    SECTION("constant") {
      SECTION("zero") {
        const Polynomial2D<float> polynomial(0);

        const auto roots = polynomial.solve();

        CHECK(roots.empty());
      }

      rc::prop("Random value", [](const float value) {
        const Polynomial2D<float> polynomial(value);

        CHECK(polynomial.order() == 0);
        CHECK(polynomial[0] == value);

        const auto roots = polynomial.solve();

        CHECK(roots.empty());
      });
    }

    SECTION("linear") {
      SECTION("zero") {
        const Polynomial2D<float> polynomial{ 0.f, 0.f };

        CHECK(polynomial.order() == 0);
        CHECK(polynomial[0] == 0.f);
        CHECK(polynomial[1] == 0.f);

        const auto roots = polynomial.solve();
        CHECK(roots.empty());
      }

      SECTION("linear only") {
        const Polynomial2D<float> polynomial{ 0.f, 1.f };

        CHECK(polynomial.order() == 1);
        CHECK(polynomial[0] == 0.f);
        CHECK(polynomial[1] == 1.f);

        const auto roots = polynomial.solve();
        CHECK(roots == std::set{ 0.f });
        CHECK(polynomial.solve() == std::set{ 0.f });
      }

      SECTION("1s") {
        const Polynomial2D<float> polynomial{ 1.f, 1.f };

        CHECK(polynomial.order() == 1);
        CHECK(polynomial[0] == 1.f);
        CHECK(polynomial[1] == 1.f);

        const auto roots = polynomial.solve();
        CHECK(roots == std::set{ -1.f });
        CHECK(polynomial.solve() == std::set{ -1.f });
      }

      rc::prop("Random coefficients", [](const float constant) {
        const auto linear = *rc::gen::nonZero<float>();
        const Polynomial2D<float> polynomial{ constant, linear };

        RC_ASSERT(polynomial.order() == 1);
        RC_ASSERT(polynomial[0] == constant);
        RC_ASSERT(polynomial[1] == linear);

        const auto solutions = polynomial.solve();
        const auto expected =  -constant / linear;

        // due to the weirdness of floating point, we can't check this simply
        // most of the time
        RC_SUCCEED_IF(solutions == std::set{ expected });

        CHECK_THAT(*solutions.begin(),
                   WithinRel(expected, 0.001) or WithinAbs(expected, 0.000001));
      });
    }

    SECTION("quadratic") {
      SECTION("zero") {
        const Polynomial2D<float> polynomial{ 0.f, 0.f, 0.f };

        CHECK(polynomial.order() == 0);
        CHECK(polynomial[0] == 0.f);
        CHECK(polynomial[1] == 0.f);
        CHECK(polynomial[2] == 0.f);

        CHECK(polynomial.solve().empty());
      }

      SECTION("quad only") {
        const Polynomial2D<float> polynomial{ 0.f, 0.f, 1.f };

        CHECK(polynomial.order() == 2);
        CHECK(polynomial[0] == 0.f);
        CHECK(polynomial[1] == 0.f);
        CHECK(polynomial[2] == 1.f);

        CHECK(polynomial.solve() == std::set{ 0.f });
      }

      SECTION("From multiplied linear `Polynomial`s") {
        SECTION("Simple") {
          const Polynomial2D<float> lin1{ 5.f, 1.f };
          const Polynomial2D<float> lin2{ 4.f, 1.f };

          const auto poly = lin1 * lin2;

          CHECK(poly.solve() == std::set{ -4.f, -5.f });
        }

        SECTION("Less intuitive") {
          const Polynomial2D<float> lin1{ 5.f, 2.f };
          const Polynomial2D<float> lin2{ 4.f, 2.f };

          const auto poly = lin1 * lin2;

          CHECK(poly.solve() == std::set{ -2.f, -2.5f });
        }
      }

      rc::prop("Random coefficients", [](const float constant) {
        const auto linear = *rc::gen::nonZero<float>();
        const auto quadratic = *rc::gen::nonZero<float>();
        const Polynomial2D<float> polynomial{ constant, linear, quadratic };

        RC_ASSERT(polynomial.order() == 2);
        RC_ASSERT(polynomial[0] == constant);
        RC_ASSERT(polynomial[1] == linear);
        RC_ASSERT(polynomial[2] == quadratic);

        const auto roots = polynomial.solve();
        // ...
      });
    }
  }

  SECTION("calculus") {
    SECTION("`derive`") {
      rc::prop("constant", [](const float value) {
        const Polynomial2D<float> polynomial{ value };

        RC_ASSERT(polynomial.derive() == Polynomial2D<float>{});
      });

      rc::prop("linear", [](const float constant, const float linear) {
        const Polynomial2D<float> polynomial{ constant, linear };

        RC_ASSERT(polynomial.derive() == Polynomial2D<float>{ linear });
      });
    }

    SECTION("`antiderive`") {
    }

    SECTION("`integrate`") {
    }
  }

  SECTION("copy") {
    rc::prop("ctor", [](const float constant, const float linear, const float quadratic) {
      const Polynomial2D<float> poly1{ constant, linear, quadratic };
      const Polynomial2D<float> poly2(poly1);

      RC_ASSERT(poly1 == poly2);

      RC_ASSERT(poly1[0] == poly2[0]);
      RC_ASSERT(poly1[1] == poly2[1]);
      RC_ASSERT(poly1[2] == poly2[2]);
    });

    SECTION("operator") {
      rc::prop("elided", [](const float constant, const float linear, const float quadratic) {
        const Polynomial2D<float> poly1{ constant, linear, quadratic };
        const Polynomial2D<float> poly2 = poly1;

        RC_ASSERT(poly1 == poly2);
      });

      rc::prop("mutable", [](const float constant, const float linear, const float quadratic) {
        const Polynomial2D<float> poly1{ constant, linear, quadratic };
        Polynomial2D<float> poly2;

        RC_ASSERT(poly1 != poly2);

        poly2 = poly1;

        RC_ASSERT(poly1 == poly2);
      });
    }
  }

  SECTION("Arithmetic") {
    SECTION("Addition") {
      SECTION("Constant poly") {
        SECTION("constant additive") {
          rc::prop("zero", [](const float value, const float input) {
            const Polynomial2D polynomial(0.f);

            const auto new_poly = polynomial + value;
            RC_ASSERT(new_poly(input) == value);
          });

          rc::prop("random value", [](const float coefficient, const float value, const float input) {
            const Polynomial2D polynomial(coefficient);

            const auto new_poly = polynomial + value;
            RC_ASSERT(new_poly(input) == coefficient + value);
          });
        }

        SECTION("linear additive") {
          rc::prop("zero", [](const float constant, const float linear, const float input){
            const Polynomial2D polynomial(0.f);
            const Polynomial2D additive{constant, linear};

            const auto new_poly = polynomial + additive;

            RC_ASSERT((new_poly(input) - additive(input)) <= 0.00001);
            RC_ASSERT((new_poly(input) - ((input * linear) + constant)) <= 0.00001);
          });

          rc::prop("zero", [](const float value, const float constant, const float linear, const float input){
            const Polynomial2D polynomial(value);
            const Polynomial2D additive{constant, linear};

            const auto new_poly = polynomial + additive;
            RC_ASSERT(new_poly(input) == additive(input) + value);
            RC_ASSERT(new_poly(input) == (input * linear) + constant + value);
            RC_ASSERT(new_poly(input) == polynomial(input) + additive(input));
          });
        }
      }

      SECTION("Linear poly") {
        SECTION("constant additive") {
          rc::prop("zero", [](const float constant, const float linear, const float additive, const float input) {
            const Polynomial2D polynomial{constant, linear};

            const auto new_poly = polynomial + additive;
            CHECK_THAT(new_poly(input),
                  Catch::Matchers::WithinRel(polynomial(input) + additive)
              and Catch::Matchers::WithinRel((linear * input) + (constant + additive))
            );
          });
        }

        SECTION("linear additive") {
          rc::prop("zero", [](const float constant, const float linear, const float additive_constant, const float additive_linear, const float input) {
            const Polynomial2D polynomial{constant, linear};
            const Polynomial2D additive{additive_constant, additive_linear};

            const auto new_poly = polynomial + additive;

            CHECK_THAT(new_poly(input),
                  Catch::Matchers::WithinRel(polynomial(input) + additive(input))
              and Catch::Matchers::WithinRel(((linear + additive_linear) * input) + (constant + additive_constant))
            );
          });
        }
      }
    }

    SECTION("Subtraction") {
    }

    SECTION("Multiplication") {
    }

    SECTION("Division") {
    }
  }

  // auto operator<=>(const Polynomial2D&, const Polynomial2D&) noexcept = default;
}
