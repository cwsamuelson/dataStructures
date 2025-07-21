#pragma once

#include <error_help.hh>

#include <atomic>

namespace flp {

template<typename Type>
struct Queue {
  struct Node {
    // Value does not need to be atomic, so long as `pop` is the only means to
    //  retrieve the value.
    // In general, allow the user to determine if atomicity is necessary by
    //  specifying `Type` to be `std::atomic<Type>`
    Type value;

    std::atomic<Node*> next = nullptr;
  };

  ~Queue() {
    while (not empty()) {
      pop();
    }
  }

  Type pop() {
    Node* old_head = head.load();
    Node* new_head = nullptr;

    do {
      if (old_head != nullptr) {
        new_head = old_head->next.load();
      }
    } while (not head.compare_exchange_strong(old_head, new_head));

    VERIFY(old_head != nullptr, "Nothing to pop");

    const auto result = std::move(old_head->value);

    if (head.load() == nullptr) {
      tail.store(head.load());
    }

    delete old_head;
    return result;
  }

  void push(const Type& value) {
    Node* old_tail = tail.load();
    auto* const new_tail = new Node(value);

    while (not tail.compare_exchange_strong(old_tail, new_tail))
    {}

    if (old_tail == nullptr) {
      // if `old_tail` stops being nullptr, somebody else changed it...
      while (not head.compare_exchange_strong(old_tail, new_tail) and old_tail == nullptr)
      {}
    } else {
      old_tail->next = new_tail;
    }
  }

  [[nodiscard]]
  bool empty() const noexcept {
    return head == nullptr and tail == nullptr;
  }

  std::atomic<Node*> head = nullptr;
  std::atomic<Node*> tail = nullptr;
};

}
