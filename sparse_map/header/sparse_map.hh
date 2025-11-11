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

  [[nodiscard]]
  bool contains(const Key key) const noexcept {
    return key < sparse_data.size()
       and sparse_data.at(key) < dense_data.size()
       and dense_data.at(sparse_data.at(key)) == key;
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
    if (contains(key)) {
      return;
    }

    if (sparse_data.size() <= key) {
      sparse_data.resize(key + 1, unlikely);
    }

    dense_data.resize(dense_data.size() + 1, unlikely);
    value_data.emplace_back(std::forward<Args>(args)...);

    dense_data.back()   = key;
    sparse_data.at(key) = dense_data.size() - 1;
  }

  void insert(const Key key, Value value) {
    if (contains(key)) {
      return;
    }

    if (sparse_data.size() <= key) {
      sparse_data.resize(key + 1, unlikely);
    }

    dense_data.resize(dense_data.size() + 1, unlikely);
    value_data.push_back(value);

    dense_data.back()   = key;
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
    std::swap(value_data.at(index), value_data.back());
    // then the sparse data indexes must be updated
    sparse_data.at(dense_data.at(index)) = index;

    dense_data.pop_back();
    value_data.pop_back();
  }

  void clear() noexcept {
    dense_data.clear();
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
      sparse_data.resize(min_size, unlikely);
      dense_data.resize(min_size, unlikely);
      value_data.reserve(min_size);
    }
  }

  struct Iterator {
    friend bool operator==(const Iterator& lhs, const Iterator& rhs) noexcept = default;
    friend auto operator<=>(const Iterator& lhs, const Iterator& rhs) noexcept = default;

    std::tuple<const Key&, Value&> operator*(this auto&& self) {
      return { *self.dense_iterator, *self.value_iterator };
    }

    pointer operator->(this auto&& self) noexcept {
      return &self.block_it->data.at(self.index).get();
    }

    Iterator& operator++(){
      return *this;
    }
    Iterator operator++(int){}

    Iterator& operator--(){
      return *this;
    }
    Iterator operator--(int){}

    typename std::vector<Key>::iterator dense_iterator;
    typename std::vector<Value>::iterator value_iterator;
  };

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

  size_t element_count{};
};

} // namespace flp
