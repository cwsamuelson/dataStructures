#include "context.hh"

#include <vector>

namespace flp {

namespace {
std::vector<Context> ContextStack;
struct GlobalContext {
  GlobalContext() {
    ContextStack.emplace_back();
  }
  ~GlobalContext() {
    ContextStack.pop_back();
  }
};
// this variable may never be directly used
// it's being used to setup the default context
[[maybe_unused]] GlobalContext global_context;
} // namespace

ScopedContext::ScopedContext(Context context) {
  PushContext(std::move(context));
}

ScopedContext::~ScopedContext() {
  PopContext();
}

void PushContext(Context context) {
  ContextStack.emplace_back(std::move(context));
}

void PopContext() {
  ContextStack.pop_back();
}

// where to create base context?
const Context& GetContext() {
  return ContextStack.back();
}

} // namespace flp
