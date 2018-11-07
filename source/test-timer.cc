#include<chrono>

#include<catch.hpp>

#include<timer.h>

using namespace std;
using namespace std::chrono_literals;

TEST_CASE( "", "[timer]" ){
  SECTION( "Delayed execution" ){
    timer t;

    auto start = chrono::high_resolution_clock::now();
    decltype( start ) end;

    auto f = t.delayed( [&](){
      end = chrono::high_resolution_clock::now();
      return 1;
    }, 5ms );

    REQUIRE( f.get() == 1 );

    REQUIRE( end - start <= 7ms );
    REQUIRE( end - start >= 3ms );
  }

  SECTION( "Scheduled execution" ){
    timer t;

    auto start = chrono::high_resolution_clock::now();
    auto start_time = start + 10ms;
    decltype( start_time ) end_time;

    auto f = t.schedule( [&](){
      end_time = chrono::high_resolution_clock::now();
      return 2;
    }, start_time );

    REQUIRE( f.get() == 2 );

    REQUIRE( end_time - start_time <= 12ms );
    REQUIRE( end_time - start_time >= 8ms );
  }
}
