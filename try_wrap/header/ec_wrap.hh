#pragma once

namespace flp {

template<typename Checker, typename Functor>
struct ECWrap {
  Checker checker;
  Functor operation;

  template<typename Check, typename Func>
  ECWrap(Check&& check, Func&& func) noexcept
    : checker(std::forward<Check>(check))
    , operation(std::forward<Func>(func))
  {}

  template<typename ...Args>
    requires std::is_void_v<std::invoke_result_t<Functor, Args...>>
  void operator()(Args&&... args) && {
    std::invoke(std::move(operation), std::forward<Args>(args)...);
  }

  template<typename ...Args>
    requires (not std::is_void_v<std::invoke_result_t<Functor, Args...>>)
    and std::same_as<bool, std::invoke_result_t<Checker, std::invoke_result_t<Functor, Args...>>>
  [[nodiscard]]
  decltype(auto) operator()(Args&&... args) && {
    auto result = std::invoke(std::move(operation), std::forward<Args>(args)...);
    VERIFY(std::invoke(std::move(checker), result), "");
    return result;
  }
};

}

