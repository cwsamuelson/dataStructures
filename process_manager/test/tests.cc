#include <proc_mon.hh>

#include <catch2/catch_all.hpp>

using namespace flp;

SCENARIO("Process Manager default init empty") {
  ProcessMonitor<size_t> scheduler;
  CHECK(scheduler.empty());
  CHECK(scheduler.size() == 0);

  scheduler.clear();
  CHECK(scheduler.empty());
  CHECK(scheduler.size() == 0);
}

SCENARIO("Adding functors to the manager") {
  ProcessMonitor<size_t> scheduler;

  GIVEN("Basic set of simple 'processes'") {
    scheduler.spawn([]() {});
    scheduler.spawn([](size_t) {});
    scheduler.spawn([]() {
      return std::nullopt;
    });
    scheduler.spawn([](size_t) {
      return std::nullopt;
    });
    scheduler.spawn([]() {
      return std::make_optional<bool>(true);
    });
    scheduler.spawn([](size_t) {
      return std::make_optional<bool>(true);
    });
    scheduler.spawn([]() {
      return std::make_optional<bool>(false);
    });
    scheduler.spawn([](size_t) {
      return std::make_optional<bool>(false);
    });
    scheduler.spawn([](size_t) -> std::optional<bool> {
      throw std::runtime_error("");
    });

    THEN("The process list reflects the tasks") {
      CHECK(scheduler.size() == 9);
    }

    WHEN("The list is cleaned") {
      scheduler.clean();

      THEN("No procs are removed; all are active") {
        CHECK(scheduler.size() == 9);
      }
    }

    WHEN("The scheduler runs") {
      scheduler(0);

      THEN("All processes are still listed") {
        CHECK(scheduler.size() == 9);
      }

      AND_WHEN("The process list is cleaned") {
        scheduler.clean();
        THEN("The completed processes are removed from the list") {
          CHECK(scheduler.size() == 4);
        }
      }
    }
  }
}
