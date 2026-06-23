#include <type_map.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

TEST_CASE("`Type Map`") {
  TypeMap<TVPair<int, 42>> tm;
}
