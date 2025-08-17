#pragma once

#include <type_pack.hh>

#include <functional>

namespace flp {

template<typename, typename...>
struct Curryable;

template<typename Ret, typename... Args, typename ...Parameters>
struct Curryable<Ret(Args...), Parameters...> {
  template<typename ...Ts>
  struct CurryHelper {
    template<typename ...Input>
    using type = Curryable<Ret(Args..., Ts...), Parameters..., Input...>;
  };

  template<typename Functor>
  Curryable(Functor&& functor)
    : function(std::forward<Functor>(functor))
  {}

  //template<typename ...Input>
  //decltype(auto) operator()(Input&& ...args) {
  //  return typename TypePack<Args...>::template Drop<sizeof...(Input)>::template Rebind<CurryHelper> {
  //    [this, inputs = ...std::forward<Input>(args)]() {
  //      function(parameters, inputs...);
  //      return std::apply(function, parameters);
  //    }
  //  };
  //}

  template<typename ...Arguments>
    requires (sizeof...(Arguments) == sizeof...(Args))
  Ret operator()(Arguments&&... args) {
    return function(std::forward<Arguments>(args)...);
  }

  std::tuple<Parameters...> parameters;
  std::function<Ret(Args...)> function;
};

}
