#pragma once

#include <array>
#include <cstddef>
#include <inplace_vector>
#include <ranges>

namespace flp {

template<typename Key, typename Value, size_t ChildMaximum>
struct BTree {
  using value_type = std::pair<Key, Value>;

  struct Node {
    std::inplace_vector<value_type, ChildMaximum - 1> elements;
    std::inplace_vector<Node*, ChildMaximum> children;
  };

  Node root;

  static constexpr NodeMinimum = ChildMaximum / 2;

  [[nodiscard]]
  bool empty() const noexcept {
    return root.elements.empty();
  }

  template<typename KType>
  Value& operator[](const KType& key) {
    for (const auto& [i, zipped] :
      std::views::enumerate(
        std::views::zip(root.elements, root.children))) {
      const auto& [element, child] = zipped;
    }
  }
};

} // namespace flp
