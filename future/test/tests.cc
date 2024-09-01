#include <future.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

TEST_CASE("using a future") {
  SECTION("Through a promise") {
    Promise<int> promise;
    auto         future = promise.get_future();

    CHECK(future.valid());
    CHECK(not future.ready());

    promise.set_value(42);
    CHECK(future.valid());
    CHECK(future.ready());

    CHECK(future.get() == 42);
  }

  SECTION("Using continuations") {
    SECTION("Same type") {
      Promise<int> promise;
      auto         future = promise.get_future().then([](int value) {
        return value * 2;
      });

      promise.set_value(42);
      CHECK(future.get() == 84);
    }
    SECTION("Change types") {
      Promise<int> promise;

      auto first  = promise.get_future();
      auto second = first.then([](int value) {
        return static_cast<float>(value * 2);
      });

      promise.set_value(42);

      CHECK(first.get() == 42);
      CHECK(second.get() == 84.0f);
    }
  }
}
