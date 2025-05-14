#pragma once

#include <allocator/std_wrapper.hh>

#include <set>

namespace flp::Contextual {

template<typename Key, typename Compare = std::less<Key>, typename Allocator = StdAllocWrapper<Key>>
  // requires Allocator is context aware
using Set = std::set<Key, Compare, Allocator>;

template<typename Key, typename Compare = std::less<Key>, typename Allocator = StdAllocWrapper<Key>>
  // requires Allocator is context aware
using MultiSet = std::multiset<Key, Compare, Allocator>;

}
