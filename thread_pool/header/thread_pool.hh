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
    queue.push(std::forward<Function>(function));
  }

  void stop();

  void run();

private:

  void run_thread(std::stop_token stop_token);

  size_t thread_count{};
  std::vector<std::jthread> threads;
  Queue<std::function<void()>> queue;
};

} // namespace flp
