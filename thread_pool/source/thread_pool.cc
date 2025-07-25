#include "thread_pool.hh"

#include <functional>

namespace flp {

ThreadPool::ThreadPool(const size_t thread_count) {
  threads.reserve(thread_count);

  for (size_t i{}; i < thread_count; ++i) {
    threads.emplace_back(std::bind_front(&ThreadPool::run, this));
  }
}

void ThreadPool::run(std::stop_token stop_token) {
  while (not stop_token.stop_requested()) {
    auto work = queue.pop();
    if (work.has_value()) {
      work.value()();
    }
  }
}

}
