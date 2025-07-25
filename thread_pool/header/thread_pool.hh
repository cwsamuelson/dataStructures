#pragma once

#include "queue.hh"

#include <thread>
#include <utility>
#include <vector>

namespace flp {

struct ThreadPool {
  ThreadPool(size_t tcount);

  template<typename Function>
  void post(Function&& function) {
    work.push(std::forward<Function>(function));
  }

  void run();

  void stop();

private:
  void run_thread(std::stop_token stop_token);

  size_t thread_count{};
  flp::Queue<std::function<void()>> work;
  std::vector<std::jthread> threads;
};

} // namespace flp

