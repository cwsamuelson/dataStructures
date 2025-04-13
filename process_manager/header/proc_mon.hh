#pragma once


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

template<typename Delta>
struct ProcessMonitor {
  struct Process {
    std::vector<Process> children;
  };

  void update(const Delta delta) {
    for (auto& process : processes) {
      process.execute(delta);
    }
  }

  void operator()(const Delta delta) {
    update(delta);
  }

  std::vector<Process> processes;
};

} // namespace flp

