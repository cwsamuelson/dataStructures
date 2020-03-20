#define CATCH_CONFIG_MAIN

#include<catch2/catch.hpp>

#include <pager.hh>

TEST_CASE("It's basically just an array", "[pager]") {
  constexpr size_t object_count = 5;
  constexpr size_t page_size = object_count;

  gsw::pager<unsigned int> p(object_count, page_size);

  for(size_t i = 0; i < object_count; ++i) {
    p[i] = i;
  }

  for(size_t i = 0; i < object_count; ++i) {
    CHECK(p[i] == i);
  }
}

TEST_CASE("Not enough room", "[pager]") {
  constexpr size_t object_count = 5;
  constexpr size_t page_size = 1;

  gsw::pager<unsigned int> p(object_count, page_size);

  for(size_t i = 0; i < object_count; ++i) {
    p[i] = i;
  }

  for(size_t i = 0; i < object_count; ++i) {
    CHECK(p[i] == i);
  }
}

TEST_CASE("Multiple pages", "[pager]") {
  gsw::pager<unsigned int> p(10, 2, 3);

  for(size_t i = 0; i < 10; ++i) {
    p[i] = i;
  }

  for(size_t i = 0; i < 10; ++i) {
    CHECK(p[i] == i);
  }
}

