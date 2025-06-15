#pragma once

#include <allocator/basic.hh>
#include <frame.hh>
#include <logger/basic.hh>

#include <memory>
#include <stack>

namespace flp {

struct ContextStack {
  std::stack<ContextFrame> stack;

  ContextStack() {
    stack.push({
      std::make_shared<STDAllocator>(),
      std::make_shared<STDLogger>(),
    });
  }

  void push(ContextFrame frame) {
    stack.push(frame);
  }

  void pop() {
    stack.pop();
  }

  const ContextFrame& context() const {
    return stack.top();
  }
};

}
