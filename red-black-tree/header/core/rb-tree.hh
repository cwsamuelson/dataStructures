#pragma once

#include <memory>

namespace flp {

template<typename Key, typename Value>
struct RBTree {
  struct Node {
    Node(Key k, Value v)
      : key(std::move(k))
      , value(std::move(v))
    {}

    const Key key;
    Value value;

    void insert(Key new_key, Value new_value) {
      if (new_key < key) {
        if (left == nullptr) {
          left = std::make_unique<Node>(std::move(new_key), std::move(new_value));
          return;
        }

        left->insert(std::move(new_key), std::move(new_value));
      } else if (new_key > key) {
        if (right == nullptr) {
          right = std::make_unique<Node>(std::move(new_key), std::move(new_value));
          return;
        }

        right->insert(std::move(new_key), std::move(new_value));
      } else {
        // this node.
      }
    }

    Value find(const Key& test_key) const {
      if (test_key == key) {
        return value;
      } else if(test_key < key) {
        if (left != nullptr) {
          return left->find(test_key);
        }
      } else if(test_key > key) {
        if (right != nullptr) {
          return right->find(test_key);
        }
      }

      throw std::runtime_error("Key not found");
    }

    [[nodiscard]]
    size_t size() const noexcept {
      size_t total{1};

      if (left != nullptr) {
        total += left->size();
      }

      if (right != nullptr) {
        total += right->size();
      }

      return total;
    }

    [[nodiscard]]
    bool contains(const Key& test_key) const {
      if (test_key == key) {
        return true;
      } else if (test_key < key and left != nullptr) {
        return left->contains(test_key);
      } else if (test_key > key and right != nullptr) {
        return left->contains(test_key);
      } else {
        return false;
      }
    }

    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;
  };

  [[nodiscard]]
  bool empty() const noexcept {
    return root == nullptr;
  }

  [[nodiscard]]
  size_t size() const noexcept {
    if (root == nullptr) {
      return 0;
    }
    
    return root->size();
  }

  void insert(Key key, Value value) {
    if (root == nullptr) {
      root = std::make_unique<Node>(std::move(key), std::move(value));

      return;
    }

    root->insert(std::move(key), std::move(value));
  }

  [[nodiscard]]
  Value find(const Key& key) const {
    if (root == nullptr) {
      throw std::runtime_error("Key not found");
    }

    return root->find(key);
  }

  [[nodiscard]]
  bool contains(const Key& key) const {
    if (root == nullptr) {
      return false;
    }

    return root->contains(key);
  }

  std::unique_ptr<Node> root;
};

} // namespace flp
