#include "context.hh"

#include <vector>

namespace flp {

namespace {
struct [[nodiscard]] GlobalContextStack {
  GlobalContextStack() noexcept {
    stack.emplace_back();
  }
  GlobalContextStack(const GlobalContextStack&) = delete;
  GlobalContextStack(GlobalContextStack&&)      = delete;

  GlobalContextStack& operator=(const GlobalContextStack&) = delete;
  GlobalContextStack& operator=(GlobalContextStack&&)      = delete;

  ~GlobalContextStack() noexcept {
    stack.pop_back();
  }

  std::vector<Context> stack;
};

GlobalContextStack global_context;
} // namespace

Context::Context()
  : logger(GetContext().logger)
  , allocator(GetContext().allocator)
  , error_contract(GetContext().error_contract) {}

ScopedContext::ScopedContext()
  : ScopedContext(Context {}) {}

ScopedContext::ScopedContext(Context context) {
  PushContext(std::move(context));
}

ScopedContext::~ScopedContext() {
  PopContext();
}

void PushContext(Context context) {
  global_context.stack.emplace_back(std::move(context));
}

void PopContext() {
  global_context.stack.pop_back();
}

// where to create base context?
const Context& GetContext() {
  return global_context.stack.back();
}

} // namespace flp
