#pragma once

#include "error.hh"

namespace flp {

enum ErrorPolicy {
  Exception,
  ErrorCode,

  Throw = Exception,
  Return = ErrorCode,
};

template<typename Type, typename Error = flp::Error>
struct Result {
  using enum ErrorPolicy;

  constexpr
  Result()
  // get current error policy from context stack
  //  : policy(error_policy())
  {}
  constexpr
  Result(const ErrorPolicy p)
    : policy(p)
  {}

  constexpr
  Result(const Type&)
  {}

  constexpr
  Result(Type&&)
  {}

  template<typename ...Args>
  constexpr
  Result(Args&& ...args)
    : value(Type(std::forward<Args>(args)...));
  {}

  constexpr
  Result(const Result&) = delete;

  constexpr
  Result& operator=(const Result&) = delete;

  operator Type() noexcept && {
    return std::move();
  }

  ErrorPolicy policy = Throw;
  std::variant<Type, Error> value;
};

}
