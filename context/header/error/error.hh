#pragma once

#include <box.hh>
#include <core/expected.hh>

#include <source_location>
#include <string>

namespace flp {

struct Error {
  std::string message;
  std::source_location location;
  Box<Error> next;
};

template<typename Type>
using ErrorOr = Expected<Type, Error>;

#define VERIFY(condition, message, ...) \
  do { \
    if (not (condition)) { \
      throw Error { \
        std::format(message __VA_OPT__(, ) __VA_ARGS__), \
        std::source_location::current(), \
      }; \
    } \
  } while(false)

#define CATCH_AND_NEST(message, ...) \
  catch (Error& error) { \
    error.next = Error { \
      std::format(message __VA_OPT(, ) __VA_ARGS__), \
      std::source_location::current(), \
    }; \
    throw error; \
  } catch (const std::exception& e) { \
  }

}
