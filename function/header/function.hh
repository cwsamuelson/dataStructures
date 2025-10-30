#pragma once

#include <memory>

namespace flp {

template<typename>
struct Function;

template<typename ReturnType, typename ...Arguments>
struct Function<ReturnType(Arguments...)> {
  template<typename Functor>
  Function(Functor&& functor)
    : implementation(std::make_unique<Implementation<Functor>>(std::forward<Functor>(functor)))
  {}

  struct Interface {
    virtual ReturnType call(Arguments&& ...arguments) = 0;
  };

  template<typename Type>
  struct Implementation : Interface {
    Type implementation;

    ReturnType call(Arguments&& ...arguments) override {
      return implementation(std::forward<Arguments>(arguments)...);
    }
  };

  template<typename ...Args>
  ReturnType operator()(Args&& ...args) {
    return implementation->call(std::forward<Args>(args)...);
  }

  std::unique_ptr<Interface> implementation;
};

} // namespace flp
