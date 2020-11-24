#define CATCH_CONFIG_MAIN

#include<catch2/catch.hpp>

#include <pager.hh>

using namespace gsw;

TEST_CASE("It's basically just an array", "[pager]") {
  for(size_t i = 0; i < 100; ++i) {
    size_t object_count = i;
    size_t page_size = object_count;

    pager<unsigned int> p(object_count, page_size);

    for(size_t i = 0; i < object_count; ++i) {
      p[i] = i;
    }

    for(size_t i = 0; i < object_count; ++i) {
      CHECK(p[i] == i);
    }
  }
}

TEST_CASE("Not enough room", "[pager]") {
  for(size_t i = 0; i < 100; ++i) {
    for(size_t j = 1; j < 100; ++j) {
      size_t object_count = i;
      size_t page_size = j;

      pager<unsigned int> p(object_count, page_size);

      for(size_t i = 0; i < object_count; ++i) {
        p[i] = i;
      }

      for(size_t i = 0; i < object_count; ++i) {
        CHECK(p[i] == i);
      }
    }
  }
}

TEST_CASE("Multiple pages", "[pager]") {
  for(size_t i = 1; i < 100; ++i) {//page size must be at least 1
    for(size_t j = 0; j < 100; ++j) {
      pager<unsigned int> p(10, i, j);

      for(size_t i = 0; i < 10; ++i) {
        p[i] = i;
      }

      for(size_t i = 0; i < 10; ++i) {
        CHECK(p[i] == i);
      }
    }
  }
}

