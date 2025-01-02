#pragma once


namespace flp {

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
    return *this;
  }

  ~DoublyLinkedList() {
    clear();
  }

  void push_back(Type value) {}

  void pop_back(Type value) {}

  Type& back() noexcept {
    return tail->value;
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
