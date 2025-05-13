#pragma once

namespace Contextual {
  // basic_string
  template<typename Char, typename Traits = std::char_traits<Char>, typename Allocator = StdAllocWrapper<Char>>
      // requires Allocator is context aware
  using BasicString = std::basic_string<Char, Traits, Allocator>;
  using String = BasicString<char>;
  //using WString = BasicString<wchar>;
  // deque
  template<typename Type, typename Allocator = StdAllocWrapper<Type>>
      // requires Allocator is context aware
  using Deque = std::deque<Type, Allocator>;
  // forward_list
  //template<typename Type, typename Allocator = StdAllocWrapper<Type>>
      // requires Allocator is context aware
  //using ForwardList = std::forward_list<Type, Allocator>;
  // list
  //template<typename Type, typename Allocator = StdAllocWrapper<Type>>
      // requires Allocator is context aware
  //using List = std::list<Type, Allocator>;
  // vector
  template<typename Type, typename Allocator = StdAllocWrapper<Type>>
      // requires Allocator is context aware
  using Vector = std::vector<Type, Allocator>;
  // map
  //template<typename Key, typename Value, typename Compare = std::less<Key>, typename Allocator = StdAllocWrapper<std::pair<const Key, Value>>>
      // requires Allocator is context aware
  //using Map = std::map<Key, Value, Compare, Allocator>;
  // multimap
  //template<typename Key, typename Value, typename Compare = std::less<Key>, typename Allocator = StdAllocWrapper<std::pair<const Key, Value>>>
      // requires Allocator is context aware
  //using MultiMap = std::multimap<Key, Value, Compare, Allocator>;
  // set
  //template<typename Key, typename Compare = std::less<Key>, typename Allocator = StdAllocWrapper<std::pair<const Key, Value>>>
      // requires Allocator is context aware
  //using Set = std::set<Key, Compare, Allocator>;
  // multiset
  //template<typename Key, typename Compare = std::less<Key>, typename Allocator = StdAllocWrapper<std::pair<const Key, Value>>>
      // requires Allocator is context aware
  //using MultiSet = std::multiset<Key, Compare, Allocator>;
  // unordered_map
  //template<typename Key, typename Value, typename Hash = std::hash<Key>, typename KeyEqual = std::equal_to<Key>, typename Allocator = StdAllocWrapper<std::pair<const Key, Value>>>
      // requires Allocator is context aware
  //using UnorderedMap = std::unordered_map<Key, Value, Hash, KeyEqual, Allocator>;
  // unordered_multimap
  //template<typename Key, typename Value, typename Hash = std::hash<Key>, typename KeyEqual = std::equal_to<Key>, typename Allocator = StdAllocWrapper<std::pair<const Key, Value>>>
      // requires Allocator is context aware
  //using UnorderedMultiMap = std::unordered_multimap<Key, Value, Hash, KeyEqual, Allocator>;
  // unordered_set
  //template<typename Key, typename Hash = std::hash<Key>, typename KeyEqual = std::equal_to<Key>, typename Allocator = StdAllocWrapper<std::pair<const Key, Value>>>
      // requires Allocator is context aware
  //using UnorderedSet = std::unordered_set<Key, Hash, KeyEqual, Allocator>;
  // unordered_multiset
  //template<typename Key, typename Hash = std::hash<Key>, typename KeyEqual = std::equal_to<Key>, typename Allocator = StdAllocWrapper<std::pair<const Key, Value>>>
      // requires Allocator is context aware
  //using UnorderedMultiSet = std::unordered_multiset<Key, Hash, KeyEqual, Allocator>;
}
