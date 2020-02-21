#define CATCH_CONFIG_MAIN
#include<catch2/catch.hpp>

#include "threadPool.hh"

using namespace gsw;

TEST_CASE("Executes work given to it", "[]"){
  bool finished1 = false;
  bool finished2 = false;

  {
    threadPool pool;

    pool.addWork([&]() { finished1 = true; });
    pool.addWork([&]() { finished2 = true; });
  }

  CHECK(finished1);
  CHECK(finished2);
}

