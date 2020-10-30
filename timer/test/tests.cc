#include<chrono>

#define CATCH_CONFIG_MAIN

#include<catch2/catch.hpp>

#include<timer.h>

using namespace std;
using namespace std::chrono_literals;

TEST_CASE("", "[timer]") {
  SECTION("Wait for it"){
    auto start = chrono::high_resolution_clock::now();
    gsw::schedule_timer(5ms).wait();
    auto end = chrono::high_resolution_clock::now();

    CHECK(end - start <= 7ms);
    CHECK(end - start >= 3ms);
  }

  SECTION("Delayed behavior"){
    auto start = chrono::high_resolution_clock::now();
    decltype(start) end;
    auto t = gsw::schedule_timer(5ms, [&end](){
      end = chrono::high_resolution_clock::now();
      return 1;
    });

    CHECK(t.get() == 1);

    CHECK(end - start <= 7ms);
    CHECK(end - start >= 3ms);
  }

  SECTION("Scheduled behaviour") {
    auto start = chrono::high_resolution_clock::now();
    decltype(start) end;
    auto t = gsw::schedule_timer(start + 5ms, [&end](){
        end = chrono::high_resolution_clock::now();
        return 1;
      });

    CHECK(t.get() == 1);

    CHECK(end - start <= 7ms);
    CHECK(end - start >= 3ms);
  }

  SECTION("Cancellable"){
    bool function_called = false;
    auto start = chrono::high_resolution_clock::now();
    auto t = gsw::schedule_timer(5s, [&function_called](){
      function_called = true;
    });

    t.cancel();

    CHECK(!function_called);
    CHECK_THROWS_AS(t.get(), gsw::TimerCancelled);
    auto end = chrono::high_resolution_clock::now();
    CHECK(end - start < 5s);
  }
}
