#include <core/curryable.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

#define TEST_CALL(signature, ...) \
  do { \
    bool called = false; \
    Curryable<signature> function([&called](auto...) { \
      called = true; \
    }); \
    CHECK(not called); \
    function(__VA_ARGS__); \
    CHECK(called); \
  } while(false)

TEST_CASE("`Curryable`, usable like a normal functor") {
  TEST_CALL(void());
  TEST_CALL(void(int), 42);
  TEST_CALL(void(float), 4.2F);
  TEST_CALL(void(int, float), 1138, 4.2F);
}

TEST_CASE("`Curryable`") {
  //bool called = false;
  //Curryable<void(int, float)> functor = [&called](const int i, const float f) {
  //  called = true;
  //  CHECK(i == 42);
  //  CHECK(f == 11.38F);
  //};

  //CHECK(not called);

  //functor(42);
  //CHECK(not called);

  //called = false;
  //functor(42, 11.38F);
  //CHECK(called);

  //called = false;
  //functor(42)(11.38F);
  //CHECK(called);
}
