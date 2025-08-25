#include <smart_enum.hh>

#include <catch2/catch_all.hpp>

#include <iostream>

using namespace flp;

SMART_ENUM_DEFINE(PossibleValue, size_t, A, B, C);
SMART_ENUM_SUB_DEFINE(AssignableValue, PossibleValue, C);

TEST_CASE("`smart_enum`: sandbox") {
  PossibleValue pvalue = PossibleValue::Value::A;
  AssignableValue avalue = AssignableValue::Value::C;

  CHECK_NOTHROW(pvalue = avalue);
  CHECK_NOTHROW(avalue = pvalue);

  pvalue = PossibleValue::Value::A;
  CHECK_THROWS(avalue = pvalue);
}
