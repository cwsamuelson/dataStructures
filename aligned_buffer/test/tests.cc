#include <catch2/catch_all.hpp>

#include <aligned_buffer.hh>

using namespace flp;

struct S {
  size_t storage[500];
};

TEST_CASE("Aligned buffer") {
  STATIC_CHECK(alignof(AlignedBuffer<size_t>) == alignof(size_t));
  STATIC_CHECK(sizeof(AlignedBuffer<size_t>) == sizeof(size_t));

  STATIC_CHECK(alignof(AlignedBuffer<S>) == alignof(S));
  STATIC_CHECK(sizeof(AlignedBuffer<S>) == sizeof(S));
}

