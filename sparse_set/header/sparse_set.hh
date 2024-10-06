#pragma once

#include <concepts>
#include <vector>

// https://programmingpraxis.com/2012/03/09/sparse-sets/
// https://skypjack.github.io/2019-03-07-ecs-baf-part-2/

namespace flp {

template<std::unsigned_integral Type>
struct SparseSet {
  [[nodiscard]]
  bool contains(const Type value) const noexcept {
    return value < sparse_data.size() and sparse_data.at(value) < element_count
       and dense_data.at(sparse_data.at(value)) == value;
  }

  void insert(const Type value) {
    ensure_size(value + 1);
    dense_data.at(element_count) = value;
    sparse_data.at(value)        = element_count;
    ++element_count;
  }

  void erase(const Type value) {
    // this could be optimized, I'm sure
    if (contains(value)) {
      // incrementing the value is cheap, and ensures they no longer match
      ++dense_data.at(sparse_data.at(value));
      --element_count;
    }
  }

  void clear() noexcept {
    element_count = 0;
  }

  [[nodiscard]]
  size_t size() const noexcept {
    return element_count;
  }

  [[nodiscard]]
  bool empty() const noexcept {
    return size() == 0;
  }

  void ensure_size(const size_t min_size) {
    if (element_count < min_size) {
      sparse_data.resize(min_size, 0);
      dense_data.resize(min_size, 0);
    }
  }

  auto begin() {
    return dense_data.begin();
  }

  auto begin() const {
    return dense_data.begin();
  }

  auto end() {
    return dense_data.begin() + element_count;
  }

  auto end() const {
    return dense_data.begin() + element_count;
  }

  std::vector<Type> sparse_data;
  std::vector<Type> dense_data;

  size_t element_count {};
};

} // namespace flp
