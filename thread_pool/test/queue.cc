#include <queue.hh>

#include <catch2/catch_all.hpp>

#include <chrono>
#include <iterator>
#include <latch>
#include <random>
#include <thread>
#include <vector>

using namespace flp;

TEST_CASE("`ThreadPoll::Queue` thread safety") {
  Queue<int> queue;
  const size_t thread_count{3};
  const size_t window_size{100000};
  std::latch latch(thread_count);

  CAPTURE(thread_count, window_size);

  std::vector<std::vector<size_t>> result_lists(thread_count);
  std::vector<size_t> production_counts(thread_count);

  auto worker = [&queue, &latch, &result_lists, window_size, &production_counts]
    (std::stop_token stop_token, const size_t ID) {
    std::hash<std::thread::id> id_hasher;
    const auto offset = id_hasher(std::this_thread::get_id());
    const auto start = window_size * ID;
    auto counter = start;

    std::mt19937 generator(Catch::rngSeed() + offset);
    std::bernoulli_distribution tf_dist(.5);

    auto& results = result_lists.at(ID);
    auto& produced = production_counts.at(ID);

    latch.arrive_and_wait();

    while (not stop_token.stop_requested() and counter < (window_size * (ID + 1))) {
      if (queue.empty() and tf_dist(generator)) {
        queue.push(counter++);
        ++produced;
      } else {
        auto opt = queue.pop();
        if (opt.has_value()) {
          results.push_back(opt.value());
        }
      }
    }
  };

  std::vector<std::jthread> threads;

  for (size_t i{}; i < thread_count; ++i) {
    threads.emplace_back(worker, i);
  }

  using namespace std::chrono_literals;
  std::this_thread::sleep_for(3s);

  threads.clear();

  std::vector<size_t> remainder;
  while (not queue.empty()) {
    remainder.push_back(queue.pop().value());
  }

  result_lists.emplace_back(std::move(remainder));

  for (size_t i{}; i < thread_count; ++i) {
    for (auto& list : result_lists) {
      CHECK(not list.empty());

      // strictly increasing
      for (auto window :
            list
          | std::views::filter([i, window_size](const auto value) {
            return (value >= window_size * i) and (value < window_size * (i + 1));
          })
          | std::views::slide(2)) {

        auto first = window.begin();
        auto second = first;
        std::advance(second, 1);
        CHECK(*first < *second);
      }
    }
  }

  const auto results_sizes = result_lists | std::views::transform([](const auto& list) {
    return list.size();
  });
  const auto result_count = std::accumulate(results_sizes.begin(), results_sizes.end(), 0);

  CAPTURE(result_count);

  CHECK(result_count <= window_size * thread_count);

  CHECK(result_count == std::accumulate(production_counts.begin(), production_counts.end(), 0));
}

TEST_CASE("`ThreadPoll::Queue` behaves as queue") {
  std::mt19937 generator(Catch::rngSeed());
  std::uniform_int_distribution distribution(1, 10000);

  std::vector<size_t> canonical;

  for (size_t i{}; i < distribution(generator); ++i) {
    canonical.push_back(distribution(generator));
  }

  Queue<size_t> queue;

  CHECK(queue.empty());

  for (const auto value : canonical) {
    queue.push(value);

    CHECK(not queue.empty());
  }

  for (const auto value : canonical) {
    CHECK(value == queue.pop().value());
  }

  // Just exercising some basic alternating patterns
  for (size_t cycle_length{1}; cycle_length < 6; ++cycle_length) {
    for (size_t k{}; k < 3; ++k) {
      for (size_t i{}; i < cycle_length; ++i) {
        queue.push(i);
      }
      for (size_t i{}; i < cycle_length; ++i) {
        CHECK(queue.pop().value() == i);
      }
    }
  }
}

// attempting to create a situation that would create the 'ABA' problem.
TEST_CASE("`ThreadPoll::Queue` ABA") {
  Queue<size_t> queue;
  const size_t thread_count{3};
  const size_t window_size{100000};
  std::latch latch(thread_count);

  auto worker = [&latch](std::stop_token stop_token) {
    latch.arrive_and_wait();

    while (not stop_token.stop_requested()) {
      // this is the basic sequence that should cause ABA
      //auto keep = queue.pop().value();
      ///*auto drop = */queue.pop().value();
      //queue.push(std::move(keep));
    }
  };

  std::vector<std::jthread> threads;

  for (size_t i{}; i < thread_count; ++i) {
    threads.emplace_back(worker);
  }

  using namespace std::chrono_literals;
  std::this_thread::sleep_for(3s);

  threads.clear();
}
