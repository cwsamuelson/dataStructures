#pragma once

#include <allocator/base.hh>
#include <error/error.hh>
#include <logger/base.hh>

#include <memory>

namespace flp {

// should the context be a trait, too?
// just expecting getters to be available?
// that prevents editing the context
struct ContextFrame {
  std::shared_ptr<AllocatorBase> allocator;
  std::shared_ptr<LoggerBase> logger;
  //std::shared_ptr<> error_policy;
  // or
  //ErrorPolicy error_policy;
  // contracts
  // concurrency
  // coroutine handling?
  // parallelism # auto parallel for loops?

  //trait::Logger    logger;
  //trait::Allocator allocator;
  //// temporary allocator?
  //trait::ErrorContract error_contract;
};

}
