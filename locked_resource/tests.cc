#define CATCH_CONFIG_MAIN
#include<catch2/catch.hpp>

#include <locked_resource.hh>

TEST_CASE("", "[]"){
  gsw::locked_resource<int> lr;

  REQUIRE(true);
}
