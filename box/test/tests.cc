#include <box.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

TEST_CASE("box") {
  SECTION("Mutable") {
    Box<int> box;
    CHECK(*box == 0);
    *box = 42;
    CHECK(*box == 42);
  }

  SECTION("Immutable") {
    const Box<int> box = 42;
    CHECK(*box == 42);
    //box = 1138; // doesn't compile
    CHECK(*box != 1138);
  }
}

