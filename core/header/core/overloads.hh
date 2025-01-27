#pragma once

namespace flp {

template<typename ...Lambdas>
struct Overloads : Lambdas... {
  /*Overloads(Lambdas&&... lambdas)
    : Lambdas(lambdas)...
  {}*/

  using Lambdas::operator()...;
};

template<typename ...Lambdas>
Overloads(Lambdas...) -> Overloads<Lambdas...>;

}

