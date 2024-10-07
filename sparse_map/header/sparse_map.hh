#pragma once

#include <concepts>
#include <vector>

// https://programmingpraxis.com/2012/03/09/sparse-sets/
// https://skypjack.github.io/2019-03-07-ecs-baf-part-2/

namespace flp {

template<std::unsigned_integral Key, typename Value>
struct SparseMap {
  [[nodiscard]]
  bool contains(const Key value) const noexcept {
    return value < sparse_data.size() and sparse_data.at(value) < value_data.size()
       and dense_data.at(sparse_data.at(value)) == value;
  }

  [[nodiscard]]
  Value& at(const Key key) {
    return value_data.at(sparse_data.at(key));
  }

  [[nodiscard]]
  const Value& at(const Key key) const {
    return value_data.at(sparse_data.at(key));
  }

  template<typename ...Args>
  void emplace(const Key key, Args&& ...args) {
    const auto element_count = value_data.size();
    ensure_size(key + 1);
    value_data.emplace_back(std::forward<Args>(args)...);
    dense_data.at(element_count) = key;
    sparse_data.at(key)          = element_count;
  }

  void insert(const Key key, Value value) {
    const auto element_count = value_data.size();
    ensure_size(key + 1);
    value_data.emplace_back(std::move(value));
    dense_data.at(element_count) = key;
    sparse_data.at(key)          = element_count;
  }

  void erase(const Key value) {
    // this could be optimized, I'm sure
    if (contains(value)) {
      // swapping this value with the last valid element ensures this one is invalidated, and maintains the dense
      // invariant
      const auto index = sparse_data.at(value);
      std::swap(dense_data.at(index), dense_data.at(value_data.size() - 1));
      std::swap(value_data.at(index), value_data.at(value_data.size() - 1));
      // then the sparse data indexes must be updated
      sparse_data.at(dense_data.at(index)) = index;

      value_data.pop_back();
    }
  }

  void clear() noexcept {
    value_data.clear();
  }

  [[nodiscard]]
  size_t size() const noexcept {
    return value_data.size();
  }

  [[nodiscard]]
  bool empty() const noexcept {
    return value_data.empty();
  }

  void ensure_size(const size_t min_size) {
    if (sparse_data.size() < min_size) {
      sparse_data.resize(min_size, 0);
      dense_data.resize(min_size, 0);
      value_data.reserve(min_size);
    }
  }

  auto begin() {
    return value_data.begin();
  }

  auto begin() const {
    return value_data.begin();
  }

  auto end() {
    return value_data.end();
  }

  auto end() const {
    return dense_data.end();
  }

  std::vector<Key>   sparse_data;
  std::vector<Key>   dense_data;
  std::vector<Value> value_data;
};

} // namespace flp
