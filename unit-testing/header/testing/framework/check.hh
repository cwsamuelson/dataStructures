#pragma once

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
  } while(false);

#define CHECK_THROWS(expression)

#define STATIC_CHECK(expression)

#define ASSERT(expression)
#define ASSERT_THROWS(expression)

#define STATIC_ASSERT(expression)
