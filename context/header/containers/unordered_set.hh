#pragma once

#include <allocator/std_wrapper.hh>

#include <unordered_set>

namespace flp::Contextual {

template<typename Key, typename Hash = std::hash<Key>, typename KeyEqual = std::equal_to<Key>, typename Allocator = StdAllocWrapper<std::pair<const Key, Value>>>
  // requires Allocator is context aware
using UnorderedSet = std::unordered_set<Key, Hash, KeyEqual, Allocator>;

template<typename Key, typename Hash = std::hash<Key>, typename KeyEqual = std::equal_to<Key>, typename Allocator = StdAllocWrapper<std::pair<const Key, Value>>>
  // requires Allocator is context aware
using UnorderedMultiSet = std::unordered_multiset<Key, Hash, KeyEqual, Allocator>;

}
#pragma once

namespace flp::Contextual {
}
