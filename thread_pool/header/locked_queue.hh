#pragma once

#include <error_help.hh>

#include <mutex>
#include <optional>

namespace flp {

template<typename Type>
struct LockedQueue {
  struct Node {
    Type value;
    Node* next = nullptr;
  };

  LockedQueue() {
    auto* node = new Node;
    head = node;
    tail = node;
  }

  void push(const Type& value) {
    auto* new_node = new Node{value};

    std::lock_guard t(tail_lock);
    tail->next = new_node;
    tail = new_node;
  }

  std::optional<Type> pop() {
    std::lock_guard h(head_lock);
    auto* node = head;
    auto* new_head = node->next;

    if (new_head == nullptr) {
      return std::nullopt;
    }

    auto result = std::move(new_head->value);
    head = new_head;
    h.unlock();

    delete node;

    return result;
  }

  Node* head = nullptr;
  Node* tail = nullptr;
  std::mutex head_lock;
  std::mutex tail_lock;
};

}
