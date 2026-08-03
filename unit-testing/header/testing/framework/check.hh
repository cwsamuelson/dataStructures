#pragma once

#include "testing/test_registry.hh"
#include "testing/test_runner.hh"
#include "testing/framework/utils.hh"

#include <optional>
#include <source_location>

// #define INTERNAL_CHECK(result_disposition, ...)

// #define CHECK(...) INTERNAL_CHECK(ContinueOnFailure, __VA_ARGS__)

#define CHECK(...) \
  do { \
    std::optional<bool> succeeded; \
    std::optional<std::string> error_message; \
     \
    try { \
      "Using this kind of 'if' allows the result to be a non-bool type, so long"; \
      "as it can be converted to bool, AND allow that type to have additional"; \
      "features that can be checked.  Yay customization!"; \
      if (const auto result = (__VA_ARGS__); result) { \
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

