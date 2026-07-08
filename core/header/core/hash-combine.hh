#pragma once

#include <cstddef>

namespace flp {

// https://www.youtube.com/watch?v=78fYPix0mN4
template<typename Type>
void hash_combine(size_t& seed, const Type& value) {
  const size_t GOLDEN = 0x9e3779b9; // golden ratio magic
  seed ^= std::hash<Type>{}(value) + GOLDEN + (seed << 6) + (seed >> 2);
}

template<typename ...Args>
inline size_t hash_values(const Args& ...args) {
  size_t seed = 0;
  (hash_combine(seed, args), ...);
  return seed;
}

// Usage:
// struct TypeHasher {
//   size_t operator()(const Type& value) const {
//     return hash_values(value.member1, value.member2, ...);
//   }
// };
//
// std::unordered_map<Type, Value, TypeHasher> data_cache;

}
