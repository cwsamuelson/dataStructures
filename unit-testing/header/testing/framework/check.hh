#pragma once

#include "testing/test_registry.hh"
#include "testing/test_runner.hh"

#include <optional>
#include <source_location>

#define PASTER(x, y) x ## _ ## y
#define BUILD_NAME(base, suffix) PASTER(base, suffix)

#define UNIQUE_NAME_FROM_LINE(name) BUILD_NAME(name, __LINE__)

#define UNIQUE_NAME(name) UNIQUE_NAME_FROM_LINE(name)

#define TEST_CASE2(TestName, ...) \
  static void TestName(); \
  namespace { \
    flp::TestRegistry::instance().tests.emplace(__VA_ARGS__, &TestName); \
  } \
  static void TestName()

#define TEST_CASE(...) \
  TEST_CASE2(UNIQUE_NAME(UNIT_TEST_INTERNAL_), __VA_ARGS__)

// #define INTERNAL_CHECK(result_disposition, ...) 

// #define CHECK(...) INTERNAL_CHECK(ContinueOnFailure, __VA_ARGS__)

#define CHECK(...) \
  do { \
    std::optional<bool> succeeded; \
    std::optional<std::string> error_message; \
     \
    try { \
      if (__VA_ARGS__) { \
        succeeded = true; \
      } else { \
        succeeded = false; \
      } \
    } catch(const std::exception& e) { \
      error_message = e.what(); \
    } catch(...) { \
      error_message = "Unkown exception thrown when evaluating: " #__VA_ARGS__; \
    } \
  } while(false)

#define CHECK_THROWS(expression)
#define CHECK_NO_THROW(expression)

#define STATIC_CHECK(expression)

#define ASSERT(expression)
#define ASSERT_THROWS(expression)
#define ASSERT_NO_THROW(expression)

#define STATIC_ASSERT(expression)
