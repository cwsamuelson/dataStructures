#include<chrono>

#define CATCH_CONFIG_MAIN

#include<catch2/catch.hpp>

#include<timer.h>

using namespace std;
using namespace std::chrono_literals;

TEST_CASE("", "[timer]") {
  SECTION("Delayed execution") {
    gsw::timer t;

    auto start = chrono::high_resolution_clock::now();
    decltype(start) end;

    auto f = t.delayed([&]()
                         {
                           end = chrono::high_resolution_clock::now();
                           return 1;
                         }, 5ms);

    CHECK(f.get() == 1);

    CHECK(end - start <= 7ms);
    CHECK(end - start >= 3ms);
  }

  SECTION("Scheduled execution") {
    gsw::timer t;

    auto start = chrono::high_resolution_clock::now();
    auto start_time = start + 10ms;
    decltype(start_time) end_time;

    auto f = t.schedule([&]()
                          {
                            end_time = chrono::high_resolution_clock::now();
                            return 2;
                          }, start_time);

    CHECK(f.get() == 2);

    CHECK(end_time - start_time <= 12ms);
    CHECK(end_time - start_time >= 8ms);
  }
}
