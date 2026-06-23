#pragma once

#include <atomic>
#include <memory>

namespace flp {

template<typename Type>
struct RCPtr {
  RCPtr()
    : control_block(std::make_shared<ControlBlock>())
  {}

protected:
  struct ControlBlock {
    std::atomic<size_t> counter;
  };

  std::shared_ptr<ControlBlock> control_block;
};

} // namespace flp
