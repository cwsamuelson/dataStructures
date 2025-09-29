#pragma once

#include <array>
#include <cstddef>

namespace flp {

template<typename Type, size_t ChildCount>
struct BTree {
  struct Node {
    Type value;
    std::array<Node*, ChildCount> children{};
  };

  Node root = nullptr;
};

} // namespace flp

