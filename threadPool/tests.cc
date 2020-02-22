#define CATCH_CONFIG_MAIN
#include<catch2/catch.hpp>

#include "threadPool.hh"

using namespace gsw;

TEST_CASE("Executes work given to it", "[]"){
  bool finished1 = false;
  bool finished2 = false;

  {
    threadPool pool;

    pool.addWork([&]() { finished1 = true; });
    pool.addWork([&]() { finished2 = true; });
  }

  CHECK(finished1);
  CHECK(finished2);
}

TEST_CASE("several threads", "[]"){
  constexpr size_t thread_count = 13;
  bool finished[thread_count];
  for(auto i = 0; i < thread_count; ++i){
    finished[i] = false;
  }

  {
    threadPool pool(5);

    for(auto& thread_has_finished : finished){
      pool.addWork([&]()
                   { thread_has_finished = true; });
    }
  }

  for(auto thread_has_finished : finished){
    CHECK(thread_has_finished);
  }
}

