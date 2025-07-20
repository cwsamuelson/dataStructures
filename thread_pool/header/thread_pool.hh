#pragma once

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

  void run(std::stop_token stop_token);

  std::vector<std::jthread> threads;
};

} // namespace flp

