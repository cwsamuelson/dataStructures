//#include <scheduler.hh>

#include <catch2/catch_all.hpp>

#include <array>
#include <chrono>
#include <vector>

//using namespace flp;

struct Task {
  virtual void run() = 0;
};

struct Scheduler {
  struct Config {
    // std::chrono::time_point frequency{1ms};
    // // worst case
    // std::chrono::duration deadline{1ms};
    size_t frequency{1};
    size_t deadline{1};
  };

  struct Handle {
    Handle(std::function<void()> task, const size_t frequency, const size_t deadline)
      : task(std::move(task))
      , config{ frequency, deadline }
      , time_until_next(frequency)
    {}

    std::function<void()> task;
    Config config;

    size_t time_until_next{};
  };

  void update() {
    for (auto& handle : handles) {
      --handle.time_until_next;

      if (handle.time_until_next == 0) {
        handle.time_until_next = handle.config.frequency;
        handle.task();
      }
    }
  }

  void schedule(std::function<void()> task, const size_t frequency, const size_t deadline) {
    handles.emplace_back(std::move(task), frequency, deadline);
  }

  std::vector<Handle> handles;
};

TEST_CASE("`Scheduler`") {
  Scheduler scheduler;

  CHECK_NOTHROW(scheduler.update());

  bool task1 = false;
  bool task2 = false;

  scheduler.schedule([&task1]{ task1 = true; }, 1, 1);
  scheduler.schedule([&task2]{ task2 = true; }, 2, 1);

  CHECK(not task1);
  CHECK(not task2);

  CHECK_NOTHROW(scheduler.update());
  CHECK(task1);
  CHECK(not task2);

  task1 = false;
  task2 = false;

  CHECK_NOTHROW(scheduler.update());
  CHECK(task1);
  CHECK(task2);
}

TEST_CASE("`Scheduler`: static list") {
  // Scheduler<std::array> scheduler {
  // };
}
