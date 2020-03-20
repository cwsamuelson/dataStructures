#define CATCH_CONFIG_MAIN

#include<catch2/catch.hpp>

#include<scheduler.hh>

using namespace std;

TEST_CASE("", "[]") {
  int i = 0;
  gsw::scheduler s([&](){++i;}, 1);

  s.update(1);

  CHECK(i == 1);

  s.update(2);

  CHECK(i == 3);
}

