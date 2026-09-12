#pragma once

#include <cstddef>
#include <utility>

namespace flp {

//! @TODO conditional noexcepts
//! @TODO allocator awareness
//! @TODO context allocator awareness
//! @TODO fancy pointers
//! @TODO iterators

template<typename Type>
struct SinglyLinkedList {
private:
  // if a custom allocator is used (in the future)
  // this node layout is not very efficient
  struct Node {
    // smart pointers or raw pointers?
    Node* next = nullptr;
    Type  value;
  };

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
  SinglyLinkedList& operator=(const SinglyLinkedList& other) {
    for (Node* node = other.root; node != nullptr; node = node->next) {
      push_back(node->value);
    }

    return *this;
  }

  [[nodiscard]]
  SinglyLinkedList& operator=(SinglyLinkedList&& other) noexcept {
    root = other.root;
    other.root = nullptr;

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

  void push_back(this auto&& self, Type value) {
    Node* node = new Node {
      .next  = self.root,
      .value = std::move(value),
    };

    self.root = node;
  }

  // UB: empty container
  void pop_back() noexcept {
    Node* node = root->next;

    delete root;
    root = node;
  }

  // UB: empty container
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

  struct Iterator {
    Node* cursor{nullptr};

    Type& operator*() {
      return cursor->value;
    }

    Type* operator->() {
      return &cursor->value;
    }

    Iterator& operator++() {
      if (cursor != nullptr) {
        cursor = cursor->next;
      }
      return *this;
    }

    Iterator operator++(int) {
      auto copy = *this;
      return ++copy;
    }
  };

  Iterator begin() {
    return {root};
  }

  Iterator end() {
    return {};
  }

private:
  Node* root = nullptr;
};

} // namespace flp
