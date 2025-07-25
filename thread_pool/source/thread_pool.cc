#include "thread_pool.hh"

#include <functional>

namespace flp {

ThreadPool::ThreadPool(const size_t tcount)
  : thread_count(tcount) {
  threads.reserve(thread_count);
}

void ThreadPool::run() {
  for (size_t i{}; i < thread_count; ++i) {
    threads.emplace_back(std::bind_front(&ThreadPool::run_thread, this));
  }
}

void ThreadPool::run_thread(std::stop_token stop_token) {
  while (not stop_token.stop_requested()) {
    auto work = queue.pop();
    if (work.has_value()) {
      work.value()();
    }
  }
}

void ThreadPool::stop() {
  for (auto& thread : threads) {
    thread.request_stop();
  }
}

}
