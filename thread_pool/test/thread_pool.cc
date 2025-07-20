#include <thread_pool.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

TEST_CASE("thread pool") {
  ThreadPool pool(1);

  int x{};
  pool.execute([&x]{ x = 42; });
  CHECK(x == 42);
}
