#include <hive.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

template<size_t ObjectSize>
struct S {
  char A[ObjectSize];
};

TEST_CASE("Hive") {
  STATIC_CHECK(Hive<S<1>>::Chunk::MemoryLoss == 0);
  STATIC_CHECK(Hive<S<2>>::Chunk::MemoryLoss == 0);
  STATIC_CHECK(Hive<S<3>>::Chunk::MemoryLoss == 1);
  STATIC_CHECK(Hive<S<4>>::Chunk::MemoryLoss == 0);
  STATIC_CHECK(Hive<S<5>>::Chunk::MemoryLoss == 1);

  SECTION("Basic insert/remove") {
    Hive<int> hive;

    CHECK(hive.capacity() == 0);
    CHECK(hive.size() == 0);
    CHECK(hive.empty());

    hive.insert(0);
    CHECK(hive.capacity() == 1024);
    CHECK(hive.size() == 1);
    CHECK(not hive.empty());

    auto iter = hive.insert(1);
    CHECK(hive.capacity() >= 1024);
    CHECK(hive.size() == 2);
    CHECK(not hive.empty());

    hive.erase(iter);
    CHECK(hive.capacity() == 1024);
    CHECK(hive.size() == 1);
    CHECK(not hive.empty());

    hive.clear();
    CHECK(hive.capacity() == 0);
    CHECK(hive.size() == 0);
    CHECK(hive.empty());

    for (size_t i {}; i < 1024; ++i) {
      hive.insert(i);
    }

    CHECK(hive.capacity() == 1024);
    CHECK(hive.size() == 1024);
    CHECK(not hive.empty());

    auto last = hive.insert(1025);
    CHECK(hive.capacity() == 2048);
    CHECK(hive.size() == 1025);
    CHECK(not hive.empty());
    CHECK((*last) == 1025);

    hive.clear();
    CHECK(hive.capacity() == 0);
    CHECK(hive.size() == 0);
    CHECK(hive.empty());
  }

  SECTION("") {
    Hive<int> hive;

    hive.insert(1);
    auto iter = hive.insert(1138);
    hive.insert(42);

    CHECK(*iter == 1138);

    CHECK(hive.size() == 3);
    hive.erase(iter);
    CHECK(hive.size() == 2);

    CHECK(*hive.begin() == 1);
    CHECK(*(++hive.begin()) == 42);
    CHECK(*(--hive.end()) == 42);
    CHECK(*(--(--hive.end())) == 1);
  }
}

TEST_CASE("Contained object lifetimes") {}

TEST_CASE("Iterator and reference validity") {}

TEST_CASE("Random erasure") {}

TEST_CASE("Only one object alive per chunk") {}
