#include <number.hh>
#include <binary_expression.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

TEST_CASE("`Equation`: `Value`") {
  SECTION("`Value` can kinda be used as a 'regular' number") {
    const Value<float> value{42.f};

    CHECK(value.evaluate() == 42.f);
    CHECK(float(value) == 42.f);
  }

  SECTION("`Value` math") {
    const Value<float> val1{42.f};
    const Value<float> val2{69.f};

    SECTION("Addition") {
      const auto addition = val1 + val2;

      CHECK(addition.evaluate() == 42 + 69);
    }

    SECTION("Subtraction") {
      const auto subtraction = val1 - val2;

      CHECK(subtraction.evaluate() == 42 - 69);
    }

    SECTION("Multiplication") {
      const auto multiplication = val1 * val2;

      CHECK(multiplication.evaluate() == 42 * 69);
    }

    SECTION("Division") {
      const auto division = val1 / val2;

      CHECK(division.evaluate() == 42.f / 69.f);
    }
  }
}
