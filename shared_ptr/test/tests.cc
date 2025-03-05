#include <shared_ptr/shared_ptr.hh>

#include <catch2/catch_all.hpp>

#include <print>

using namespace flp;

TEST_CASE("SharedPointer") {
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

    std::println("Pre");

    SECTION("reset pointer1") {
      std::println("A1");
      pointer1.reset();

      std::println("A2");
      CHECK(pointer1.use_count() == 0);
      std::println("A3");
      CHECK(pointer2.use_count() == 1);

      std::println("A4");
      CHECK(pointer1.get() == nullptr);

      std::println("A5");
      CHECK(not pointer1);
      std::println("A6");
      CHECK(pointer2);
    }

    std::println("Interstitium");

    SECTION("reset pointer2") {
      std::println("B1");
      pointer2.reset();

      std::println("B2");
      CHECK(pointer2.use_count() == 0);
      std::println("B3");
      CHECK(pointer1.use_count() == 1);

      std::println("B4");
      CHECK(pointer2.get() == nullptr);

      std::println("B5");
      CHECK(pointer1);
      std::println("B6");
      CHECK(not pointer2);
    }

    std::println("Post");
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

