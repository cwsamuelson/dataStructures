#pragma once

#include <allocator/std_wrapper.hh>

#include <unordered_map>

namespace flp::Contextual {

template<typename Key, typename Value, typename Hash = std::hash<Key>, typename KeyEqual = std::equal_to<Key>, typename Allocator = StdAllocWrapper<std::pair<const Key, Value>>>
  // requires Allocator is context aware
using UnorderedMap = std::unordered_map<Key, Value, Hash, KeyEqual, Allocator>;

template<typename Key, typename Value, typename Hash = std::hash<Key>, typename KeyEqual = std::equal_to<Key>, typename Allocator = StdAllocWrapper<std::pair<const Key, Value>>>
  // requires Allocator is context aware
using UnorderedMultiMap = std::unordered_multimap<Key, Value, Hash, KeyEqual, Allocator>;

}
