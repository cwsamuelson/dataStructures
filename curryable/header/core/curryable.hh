#pragma once

#include <functional>

namespace flp {

template<typename>
struct Curryable;

template<typename Ret, typename... Args>
struct Curryable<Ret(Args...)> {
  template<typename Functor>
  Curryable(Functor&& functor)
    : function(std::forward<Functor>(functor))
  {}

  //template<typename ...Input>
  //decltype(auto) operator()(Input&& ...args) {
  // This is the currying.  Return another curryable with different argument types
  // A `TypePack` may be useful here
  //}

  Ret operator()(Args&&... args) {
    return function(std::forward<Args>(args)...);
  }

  std::function<Ret(Args...)> function;
};

}