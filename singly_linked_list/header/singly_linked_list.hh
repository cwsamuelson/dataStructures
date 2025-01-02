#pragma once

#include <cstddef>
#include <utility>

namespace flp {

template<typename Type>
class SinglyLinkedList {
public:
  SinglyLinkedList() = default;

  SinglyLinkedList(const SinglyLinkedList& other) {
    for (Node* node = root; node != nullptr; node = node->next) {
      push_back(node->value);
    }
  }

  SinglyLinkedList(SinglyLinkedList&& other) noexcept
    : root(other.root) {
    other.root = nullptr;
  }

  [[nodiscard]]
  SinglyLinkedList& operator=(const SinglyLinkedList&) {
    return *this;
  }

  [[nodiscard]]
  SinglyLinkedList& operator=(SinglyLinkedList&&) noexcept {
    return *this;
  }

  ~SinglyLinkedList() {
    clear();
  }

  [[nodiscard]]
  bool empty() const noexcept {
    return root == nullptr;
  }

  [[nodiscard]]
  size_t size() const noexcept {
    size_t result {};

    for (Node* node = root; node != nullptr; node = node->next) {
      ++result;
    }

    return result;
  }

  void push_back(Type value) {
    Node* node = new Node {
      .next  = root,
      .value = std::move(value),
    };

    root = node;
  }

  // undefined behaviour on empty container
  void pop_back() noexcept {
    Node* node = root->next;

    delete root;
    root = node;
  }

  // undefined behaviour on empty container
  Type& back() noexcept {
    return root->value;
  }

  void clear() {
    auto delete_nodes = [](this auto&& self, Node* node) -> void {
      if (node != nullptr) {
        self(node->next);
        delete node;
      }
    };

    delete_nodes(root);
    root = nullptr;
  }

private:
  // if a custom allocator is used (in the future)
  // this node layout is not very efficient
  struct Node {
    // smart pointers or raw pointers?
    Node* next = nullptr;
    Type  value;
  };

  Node* root = nullptr;
};

} // namespace flp
