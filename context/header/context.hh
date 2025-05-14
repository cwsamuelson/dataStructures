#pragma once

#include <allocator/base.hh>
#include <frame.hh>
#include <logger/base.hh>
#include <stack.hh>

#include <functional>
#include <memory>
#include <source_location>
#include <stack>
#include <string>

namespace flp {

thread_local inline ContextStack GlobalCtxStack{};

void push_context(ContextFrame frame) {
  GlobalCtxStack.push(frame);
}

void pop_context() {
  GlobalCtxStack.pop();
}

void push_context(std::shared_ptr<AllocatorBase> allocator) {
  push_context(ContextFrame{
    .allocator = allocator,
    .logger = GlobalCtxStack.stack.top().logger,
  });
}

void push_context(std::shared_ptr<LoggerBase> logger) {
  push_context(ContextFrame{
    .allocator = GlobalCtxStack.stack.top().allocator,
    .logger = logger,
  });
}

const ContextFrame& context() {
  return GlobalCtxStack.context();
}

auto allocator() {
  return context().allocator;
}

auto logger() {
  return context().logger;
}

struct ScopedContext {
  template<typename ...Args>
  ScopedContext(Args&& ...args) {
    push_context(std::forward<Args>(args)...);
  }

  explicit
  ScopedContext(ContextFrame context);

  ScopedContext(const ScopedContext&) = delete;
  ScopedContext(ScopedContext&&)      = delete;

  ScopedContext& operator=(const ScopedContext&) = delete;
  ScopedContext& operator=(ScopedContext&&)      = delete;

  ~ScopedContext() {
    pop_context();
  }

  template<typename Type, typename ...Args>
  static auto create(Args&& ...args) {
    return ScopedContext(std::make_shared<Type>(std::forward<Args>(args)...));
  }
};

template<typename Type, typename ...Args>
auto create_scoped_context(Args&& ...args) {
  return ScopedContext(std::make_shared<Type>(std::forward<Args>(args)...));
}

void                PushContext(ContextFrame context);
void                PopContext();
const ContextFrame& GetContext();

} // namespace flp
