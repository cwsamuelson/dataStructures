#pragma once

#include "queue.hh"

#include <thread>
#include <utility>
#include <vector>

namespace flp {

struct ThreadPool {
  ThreadPool(size_t thread_count);

  template<typename Function>
  void execute(Function&& function) {
    std::forward<Function>(function)();
  }

  template<typename Function>
  void post(Function&& function) {
    queue.push(std::forward<Function>(function));
  }

private:
  void run(std::stop_token stop_token);

  std::vector<std::jthread> threads;
  Queue<std::function<void()>> queue;
};

} // namespace flp

