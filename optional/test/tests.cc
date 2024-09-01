#include <catch2/catch_all.hpp>

#include <optional.hh>

using namespace flp;

TEST_CASE("using an optional") {
  SECTION("Defaults empty") {
    Optional<int> optional;
    CHECK(not optional);
    CHECK(not optional.has_value());
    CHECK_THROWS(optional.value());
  }
}

