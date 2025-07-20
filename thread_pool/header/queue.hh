#pragma once

#include <atomic>

namespace flp {

template<typename Type>
struct Queue {
  struct Node {
    Type value;

    Node* next = nullptr;
  };

  Type pop() {
    const auto result = std::move(head->value);
    auto* old = head;
    head = head->next;

    if (head == nullptr) {
      tail = head;
    }

    delete old;
    return result;
  }

  void push(const Type& value) {
    auto* new_node = new Node(value);

    if (tail == nullptr) {
      tail = new_node;
      head = tail;
    } else {
      tail->next = new_node;
      tail = new_node;
    }
  }

  [[nodiscard]]
  bool empty() const noexcept {
    return head == nullptr;
  }

  Node* head = nullptr;
  Node* tail = nullptr;
};

}
