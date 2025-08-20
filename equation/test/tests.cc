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
    const Value<float> v1{42.f};
    const Value<float> v2{69.f};

    const auto addition = v1 + v2;

    CHECK(addition.evaluate() == 42 + 69);
    CHECK(addition.evaluate() == 111);
  }
}
