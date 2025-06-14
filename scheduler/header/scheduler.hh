#pragma once

#include <functional>
#include <vector>

namespace flp {

// The idea is mostly inspired from:
// Working on mission critical real time embedded systems

// The scheduler system maintains tasks that require to be run regularly
// Each task should have a frequency it expects to run in order to maintain its task
// Examples include:
// - I/O polling
// - ADC monitoring
// - Watchdog
// - Temperature monitoring
// - Motor control updates
// A scheduler runs 'autonomously' and within the time domain, ensuring tasks
// are run with regularity at their expected frequency.
// The scheduler provides a task with the real-time delta-t between tasks,
// using the requested resolution (std::milli, etc provided as template param).
// The resolution of delta-t is limited by the time-keeping mechanisms available
//
// The scheduler system will make available an interface for policies for
// reporting when timings cannot be maintained.
// Built-In available policies will be made available:
// - Null
//   - Will simply run any tasks that broke their deadline as if nothing were wrong
//   - The real time difference is still reported for the task's awareness
// - Threading
//   - If a deadline is about to be broken, start a new thread for the at-risk task
//   - Requires a thread limit
//   - Requires a fallback policy for when the thread count is exceeded
// - Logging
//   - Report task causing deadline failure
//   - Report task missing its deadline
// - Abort
//   - Stop the run-loop
// - Exception
//   - Throw an exception when a task is determined to break its deadline
//
// Provide a method to validate a schedule?
// If each task provides an expected execution time, we can check whether the
// set of tasks will succeed.

template<typename>
struct FunctorAdaptor;

struct Scheduler {
  struct TaskConfig {
    time frequency{1ms};
    // worst case
    duration deadline{1ms};
  };

  struct Task {
    virtual void tick() = 0;
  };

  std::vector<Task> tasks;
};

struct FunctorAdaptor : Scheduler::Task {
  template<std::invocable<> Functor>
  FunctorAdaptor(Functor&& fn)
    : func([fn = std::move(fn)] {
      return fn();
    })
  {}

  void tick() override {
    return func(delta_t);
  }

  std::function<void()> func;
};

} // namespace flp
