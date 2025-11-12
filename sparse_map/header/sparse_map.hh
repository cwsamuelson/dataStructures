#pragma once

#include <concepts>
#include <limits>
#include <vector>

// https://programmingpraxis.com/2012/03/09/sparse-sets/
// https://skypjack.github.io/2019-03-07-ecs-baf-part-2/

namespace flp {

template<std::unsigned_integral Key, typename Value>
struct SparseMap {
  static constexpr auto unlikely = std::numeric_limits<Key>::max();

  SparseMap() = default;

  template<typename Iterator>
  SparseMap(Iterator first, Iterator last) {
    while (first != last) {
      emplace(std::get<0>(*first), std::get<1>(*first));
      ++first;
    }
  }

  [[nodiscard]]
  bool contains(const Key key) const noexcept {
    return key < sparse_data.size()
       and sparse_data.at(key) < dense_data.size()
       and dense_data.at(sparse_data.at(key)).first == key;
  }

  [[nodiscard]]
  Value& at(const Key key) {
    return dense_data.at(sparse_data.at(key)).second;
  }

  [[nodiscard]]
  const Value& at(const Key key) const {
    return dense_data.at(sparse_data.at(key)).second;
  }

  template<typename ...Args>
  void emplace(const Key key, Args&& ...args) {
    if (contains(key)) {
      return;
    }

    if (sparse_data.size() <= key) {
      sparse_data.resize(key + 1, unlikely);
    }

    dense_data.emplace_back(key, Value{std::forward<Args>(args)...});
    sparse_data.at(key) = dense_data.size() - 1;
  }

  void insert(const Key key, Value value) {
    if (contains(key)) {
      return;
    }

    if (sparse_data.size() <= key) {
      sparse_data.resize(key + 1, unlikely);
    }

    dense_data.emplace_back(key, value);
    sparse_data.at(key) = dense_data.size() - 1;
  }

  void erase(const Key key) {
    if (not contains(key)) {
      return;
    }

    // this could be optimized, I'm sure
    // swapping this key with the last valid element ensures this one is
    // invalidated, and maintains the dense invariant
    const auto index = sparse_data.at(key);
    std::swap(dense_data.at(index), dense_data.back());

    // then the sparse data indexes must be updated
    sparse_data.at(dense_data.at(index).first) = index;

    dense_data.pop_back();
  }

  void clear() noexcept {
    sparse_data.clear();
    dense_data.clear();
  }

  [[nodiscard]]
  size_t size() const noexcept {
    return dense_data.size();
  }

  [[nodiscard]]
  bool empty() const noexcept {
    return dense_data.empty();
  }

  auto begin() {
    return dense_data.begin();
  }

  auto begin() const {
    return dense_data.begin();
  }

  auto end() {
    return dense_data.end();
  }

  auto end() const {
    return dense_data.end();
  }

  std::vector<Key> sparse_data;
  std::vector<std::pair<Key, Value>> dense_data;

  size_t element_count{};
};

} // namespace flp
