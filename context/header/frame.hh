#pragma once

#include <memory>

namespace flp {

struct ContextFrame {
  std::shared_ptr<AllocatorBase> allocator;
  std::shared_ptr<LoggerBase> logger;
  // error handling
  // contracts
  // concurrency
  // parallelism # auto parallel for loops?
};

}
