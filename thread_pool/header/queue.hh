#pragma once

#include <error_help.hh>

#include <atomic>
#include <optional>

namespace flp {

template<typename Type>
struct Queue {
  struct Node;
  struct Pointer {
    Node* pointer = nullptr;
    // This participates in the solution to the ABA problem
    size_t version{};

    friend auto operator<=>(const Pointer&, const Pointer&) noexcept = default;
  };

  struct Node {
    Type value;

    std::atomic<Pointer> next;
  };

  // I'm not sure the dummy is necessary?
  // isn't it the same as nullptr?
  // unless the `dummy.version` value is used..
  Queue() {
    auto* dummy = new Node;
    head.store({.pointer = dummy});
    tail.store({.pointer = dummy});
  }

  ~Queue() {
    while (not empty()) {
      pop();
    }
  }

  void push(const Type& value) {
    auto* new_node = new Node{value};
    Pointer t;
    Pointer next;

    // loop
    while (true) {
      t = tail.load();
      next = tail.load().pointer->next.load();

      if (t == tail.load()) {
        if (next.pointer == nullptr) {
          if (t.pointer->next.compare_exchange_weak(next, {new_node, next.version + 1})) {
            break;
          }
        } else {
          tail.compare_exchange_weak(t, {next.pointer, t.version + 1});
        }
      }
    }

    tail.compare_exchange_weak(t, {new_node, t.version + 1});
  }

  std::optional<Type> pop() {
    Pointer h;
    Pointer t;
    Pointer next;
    std::optional<Type> result;

    while (true) {
      h = head.load();
      t = tail.load();
      next = h.pointer->next.load();

      if (h == head.load()) {
        if (h.pointer == t.pointer) {
          if (next.pointer == nullptr) {
            return std::nullopt;
          }
          tail.compare_exchange_weak(t, {next.pointer, tail.load().version + 1});
        } else {
          result = next.pointer->value;
          if (head.compare_exchange_weak(h, {next.pointer, h.version + 1})) {
            break;
          }
        }
      }
    }

    delete h.pointer;

    return result;
  }

  [[nodiscard]]
  bool empty() const noexcept {
    return head.load().pointer == nullptr and tail.load().pointer == nullptr;
  }

  std::atomic<Pointer> head;
  std::atomic<Pointer> tail;
};

}
