#include <shared_ptr/shared_ptr.hh>

#include <catch2/catch_all.hpp>

#include <print>

using namespace flp;

TEST_CASE("`SharedPointer`") {
  SharedPointer<int> pointer1(new int);

  CHECK(pointer1.use_count() == 1);

  REQUIRE(pointer1.get() != nullptr);

  *pointer1 = 1138;

  CHECK(*pointer1 == 1138);
  CHECK(pointer1);

  SECTION("Explicit Copy") {
    SharedPointer<int> pointer2(pointer1);

    CHECK(pointer1.use_count() == 2);
    CHECK(pointer2.use_count() == 2);
    CHECK(pointer1.get() == pointer2.get());

    CHECK(*pointer2 == 1138);
    CHECK(pointer2);

    SECTION("reset pointer1") {
      pointer1.reset();

      CHECK(pointer1.use_count() == 0);
      CHECK(pointer2.use_count() == 1);

      CHECK(pointer1.get() == nullptr);

      CHECK(not pointer1);
      CHECK(pointer2);
    }

    SECTION("reset pointer2") {
      pointer2.reset();

      CHECK(pointer2.use_count() == 0);
      CHECK(pointer1.use_count() == 1);

      CHECK(pointer2.get() == nullptr);

      CHECK(pointer1);
      CHECK(not pointer2);
    }
  }

  SECTION("Scoped Copy") {
    {
      SharedPointer<int> pointer2(pointer1);

      CHECK(pointer1.use_count() == 2);
      CHECK(pointer2.use_count() == 2);

      *pointer2 = 1138;
    }

    CHECK(pointer1);
    CHECK(pointer1.use_count() == 1);
    CHECK(*pointer1 == 1138);
  }
}
