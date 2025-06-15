#include "context.hh"

#include <vector>

namespace flp {

namespace {

thread_local inline ContextStack global_context_stack{};

} // namespace

void push_context(ContextFrame frame) {
  global_context_stack.push(frame);
}

void pop_context() {
  global_context_stack.pop();
}

void push_context(std::shared_ptr<AllocatorBase> allocator) {
  push_context(ContextFrame{
    .allocator = allocator,
    .logger = global_context_stack.stack.top().logger,
  });
}

void push_context(std::shared_ptr<LoggerBase> logger) {
  push_context(ContextFrame{
    .allocator = global_context_stack.stack.top().allocator,
    .logger = logger,
  });
}

const ContextFrame& context() {
  return global_context_stack.context();
}

std::shared_ptr<AllocatorBase> allocator() {
  return context().allocator;
}

std::shared_ptr<LoggerBase> logger() {
  return context().logger;
}

} // namespace flp
