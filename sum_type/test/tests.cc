#include <sum_type.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

TEST_CASE("sum_type") {
  enum class State {
    OK,
    Err,
  };

  SumType<State, std::string> error_or;

  using enum State;
  //TypePair<State, OK, false> tp_OK;
  //TypePair<State, Err, true, std::string> tp_Err;
  X<State, Y<State, OK>, Z<State, Err, std::string>> x;
}

