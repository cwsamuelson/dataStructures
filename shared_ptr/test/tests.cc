#include <shared_ptr/shared_ptr.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

TEST_CASE("SharedPointer") {
  SharedPointer<int> pointer(new int);

  REQUIRE(pointer.get() != nullptr);

  *pointer = 1138;

  CHECK(*pointer == 1138);
}

