#pragma once

#include <allocator/std_wrapper.hh>

#include <map>

namespace flp::Contextual {

template<typename Key, typename Value, typename Compare = std::less<Key>, typename Allocator = StdAllocWrapper<std::pair<const Key, Value>>>
  // requires Allocator is context aware
using Map = std::map<Key, Value, Compare, Allocator>;

template<typename Key, typename Value, typename Compare = std::less<Key>, typename Allocator = StdAllocWrapper<std::pair<const Key, Value>>>
  // requires Allocator is context aware
using MultiMap = std::multimap<Key, Value, Compare, Allocator>;

}
