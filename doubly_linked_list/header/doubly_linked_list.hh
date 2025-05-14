#pragma once

#include <cstddef>

namespace flp {

//! @TODO conditional noexcepts
//! @TODO allocator awareness
//! @TODO context allocator awareness
//! @TODO fancy pointers
//! @TODO iterators

template<typename Type>
class DoublyLinkedList {
public:
  DoublyLinkedList() = default;

  DoublyLinkedList(const DoublyLinkedList& other) {}

  DoublyLinkedList(DoublyLinkedList&& other) {}

  [[nodiscard]]
  DoublyLinkedList& operator=(const DoublyLinkedList& other) {
    return *this;
  }

  [[nodiscard]]
  DoublyLinkedList& operator=(DoublyLinkedList&& other) {
    head = other.head;
    tail = other.tail;

    other.head = nullptr;
    other.tail = nullptr;

    return *this;
  }

  ~DoublyLinkedList() {
    clear();
  }

  void push_front(Type value) {}

  void pop_front(Type value) {}

  void push_back(Type value) {}

  void pop_back(Type value) {}

  Type& front(this auto&& self) noexcept {
    return self.head->value;
  }

  Type& back(this auto&& self) noexcept {
    return self.tail->value;
  }

  [[nodiscard]]
  size_t size() const noexcept {
    size_t count{};

    for (auto* cursor = head; cursor != tail; cursor = cursor->next) {
      ++count;
    }

    return count;
  }

  [[nodiscard]]
  bool empty() const noexcept {
    return head == nullptr;
  }

  void clear() {
    auto delete_nodes = [](this auto&& self, Node* node) -> void {
      if (node != nullptr) {
        self(node->next);
        delete node;
      }
    };

    delete_nodes(head);
    head = nullptr;
    tail = nullptr;
  }

private:
  struct Node {
    Node* next = nullptr;
    Node* prev = nullptr;
    Type  value;
  };

  Node* head = nullptr;
  Node* tail = nullptr;
};

} // namespace flp
