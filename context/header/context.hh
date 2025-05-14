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

void push_context(ContextFrame frame);

void pop_context();

void push_context(std::shared_ptr<AllocatorBase> allocator);

void push_context(std::shared_ptr<LoggerBase> logger);

const ContextFrame& context();

std::shared_ptr<AllocatorBase> allocator();

std::shared_ptr<LoggerBase> logger();

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

} // namespace flp
