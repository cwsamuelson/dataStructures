#pragma once

#include <algorithm>
#include <functional>
#include <memory>
#include <optional>
#include <vector>

namespace flp {

// The process monitor has a collection of tasks/processes that are run with every 'tick'.
// Each process can have sub processes for success and failure.
// Provides a monadic interface for process chaining
// The process monitor provides a delta-t between ticks for maintaining real-time appearance
// The idea is mostly inspired from:
// https://github.com/skypjack/entt/blob/master/docs/md/process.md

// Thoughts:
// skypjack uses the idea of 'child' process to chain processes together
// I would like to maintain process chaining, but perhaps re-claim the idea of
// a child process by enabling a parent to communicate with a 'child' by
// creating a new idea of child, and re-naming that child as a 'follower' or
// some such.
// This results in 2 ideas:
// - Child
//   - a sub-process like in an OS
// - Follower
//   - A process that runs on `success` of the parent
//   - xor
//   - A process that runs on `failure` of the parent

template<typename>
struct FunctorAdaptor;

template<typename Delta>
struct ProcessMonitor {
  // making the process type a template parameter of processmonitor (with the
  //  constraint of inheriting from this type), can enable derived classes of
  //  processmonitor to use additional features smoothly.
  struct Process {
    virtual std::optional<bool> tick(Delta) = 0;

    [[nodiscard]]
    bool succeeded() const {
      return result.has_value() and result.value();
    }

    [[nodiscard]]
    bool failed() const {
      return result.has_value() and not result.value();
    }

    [[nodiscard]]
    bool alive() const {
      return not dead();
    }

    [[nodiscard]]
    bool dead() const {
      return result.has_value();
    }

    //void fork() {
    //}

    virtual void abort() {
      result = false;
    }

    std::optional<bool> result;
  };

  void tick(const Delta delta) {
    for (auto& process : processes) {
      if (process->alive()) {
        try {
          process->result = process->tick(delta);
        } catch (...) {
          process->result = false;
        }
      }
    }
  }

  void operator()(const Delta delta) {
    tick(delta);
  }

  [[nodiscard]]
  bool empty() const noexcept {
    return processes.empty();
  }

  [[nodiscard]]
  size_t size() const noexcept {
    return processes.size();
  }

  void clear() {
    abort();
    processes.clear();
  }

  void abort() {
    for (auto& process : processes) {
      process->abort();
    }
  }

  template<typename Proc, typename ...Args>
  void spawn(Args&& ...args) {
    processes.emplace_back(std::make_shared<Proc>(std::forward<Args>(args)...));
  }

  template<typename Func>
  void spawn(Func&& func) {
    processes.push_back(std::make_shared<FunctorAdaptor<Delta>>(std::move(func)));
  }

  void clean() {
    const auto last = std::remove_if(processes.begin(), processes.end(), [](const auto& proc) {
      return proc->dead();
    });

    processes.erase(last, processes.end());
  }

  std::vector<std::shared_ptr<Process>> processes;
};

template<typename Delta>
struct FunctorAdaptor : ProcessMonitor<Delta>::Process {
  template<std::invocable<Delta> Functor>
    requires std::convertible_to<std::invoke_result_t<Functor, Delta>, std::optional<bool>>
  FunctorAdaptor(Functor&& fn)
    : func(std::move(fn))
  {}

  template<std::invocable<Delta> Functor>
    requires (not std::convertible_to<std::invoke_result_t<Functor, Delta>, std::optional<bool>>)
  FunctorAdaptor(Functor&& fn)
    : func([fn = std::move(fn)](const Delta delta) -> std::optional<bool> {
      try {
        fn(delta);
      } catch (...) {
        return false;
      }

      return std::nullopt;
    })
  {}

  template<std::invocable<> Functor>
    requires (std::convertible_to<std::invoke_result_t<Functor>, std::optional<bool>>)
  FunctorAdaptor(Functor&& fn)
    : func([fn = std::move(fn)](const Delta)  -> std::optional<bool> {
      return fn();
    })
  {}

  template<std::invocable<> Functor>
    requires (not std::convertible_to<std::invoke_result_t<Functor>, std::optional<bool>>)
  FunctorAdaptor(Functor&& fn)
    : func([fn = std::move(fn)](const Delta)  -> std::optional<bool> {
      try {
        fn();
      } catch (...) {
        return false;
      }

      return std::nullopt;
    })
  {}

  std::optional<bool> tick(const Delta delta_t) override {
    return func(delta_t);
  }

  std::function<std::optional<bool>(Delta)> func;
};

} // namespace flp
