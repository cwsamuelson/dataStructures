#define CATCH_CONFIG_MAIN
#include<catch2/catch.hpp>

#include "threadPool.hh"

#include <thread>
#include <algorithm>

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
  using namespace std::chrono_literals;
  constexpr size_t thread_count = 13;

  bool finished[thread_count];
  for(auto& thread_check : finished){
    thread_check = false;
  }

  {
    threadPool pool(5);

    for(auto& thread_has_finished : finished){
      pool.addWork([&]()
                   { thread_has_finished = true; });
    }

    std::this_thread::sleep_for(1s);//wait for the work to actually be done
  }

  CHECK(std::all_of(finished, finished + thread_count, [](bool b){ return b; }));
}
  }
}

