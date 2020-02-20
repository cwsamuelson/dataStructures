#define CATCH_CONFIG_MAIN
#include<catch2/catch.hpp>

#include "threadPool.hh"

using namespace gsw;

TEST_CASE("", "[]"){
  threadPool pool;

  pool.addWork([](){});
}
