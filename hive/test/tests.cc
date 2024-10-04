#include <hive.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

// this struct should maybe be put into a shared location?
TEST_CASE("Hive") {
  hive<int> hive;
}
