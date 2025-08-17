#pragma once

namespace flp {

template<typename ...Lambdas>
struct Overloads : Lambdas... {
  using Lambdas::operator()...;
};

template<typename ...Lambdas>
Overloads(Lambdas...) -> Overloads<Lambdas...>;

#define Functor(functor) \
  [](auto&&... args) { \
    return functor(std::forward<decltype(args)>(args)...); \
  }

}
