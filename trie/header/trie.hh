#pragma once

#include <vector>

namespace flp {

template<typename Type>
struct Trie {
  Type value;
  std::vector<Trie> children;
  bool termaniting = false;
};

} // namespace flp

