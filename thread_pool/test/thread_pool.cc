#include <thread_pool.hh>

#include <catch2/catch_all.hpp>

#include <latch>

using namespace flp;

TEST_CASE("`ThreadPool`") {
  ThreadPool pool(1);
  std::latch latch(1);

  int x{};
  pool.execute([&x]{
    x = 42;
  });

  pool.execute([&pool, &latch]{
    pool.stop();
    latch.count_down();
  });

  CHECK(x == 0);

  pool.run();

  latch.wait();

  CHECK(x == 42);
}
