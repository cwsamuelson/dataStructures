#pragma once

#include "testing/framework/utils.hh"
#include "testing/test_registrar.hh"

#define TEST_CASE2(TestName, ...) \
  static void TestName(); \
  namespace { \
    const flp::TestAutoRegistrar UNIQUE_NAME(TestName)(std::source_location::current(), __VA_ARGS__, &TestName); \
  } \
  static void TestName()

#define TEST_CASE(...) \
  TEST_CASE2(UNIQUE_NAME(UNIT_TEST_INTERNAL_), __VA_ARGS__)
