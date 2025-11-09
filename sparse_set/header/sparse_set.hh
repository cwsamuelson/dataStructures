#pragma once

#include <concepts>
#include <cstddef>
#include <vector>

// https://programmingpraxis.com/2012/03/09/sparse-sets/
// https://skypjack.github.io/2019-03-07-ecs-baf-part-2/

namespace flp {

template<std::unsigned_integral Type>
class SparseSet {
public:
  static constexpr auto unlikely = std::numeric_limits<Type>::max();

  SparseSet() = default;

  template<typename Iterator>
  SparseSet(Iterator first, Iterator last) {
    insert(first, last);
  }

  [[nodiscard]]
  bool contains(const Type value) const noexcept {
    return value < sparse_data.size()
       and sparse_data.at(value) < dense_data.size()
       and dense_data.at(sparse_data.at(value)) == value;
  }

  void insert(const Type value) {
    if (contains(value)) {
      return;
    }

    if (sparse_data.size() <= value) {
      sparse_data.resize(value + 1, unlikely);
    }

    dense_data.resize(dense_data.size() + 1, unlikely);

    dense_data.back()     = value;
    sparse_data.at(value) = dense_data.size() - 1;
  }

  template<typename Iterator>
  void insert(Iterator first, Iterator last) {
    while (first != last) {
      insert(*first++);
    }
  }

  void erase(const Type value) {
    if (not contains(value)) {
      return;
    }

    // this could be optimized, I'm sure
    // swapping this value with the last valid element ensures this one is
    // invalidated, and maintains the dense invariant
    const auto index = sparse_data.at(value);
    std::swap(dense_data.at(index), dense_data.back());
    // then the sparse data indexes must be updated
    sparse_data.at(dense_data.at(index)) = index;

    dense_data.pop_back();
  }

  template<typename Iterator>
  void erase(Iterator first, Iterator last) {
    while (first != last) {
      erase(*first++);
    }
  }

  void shrink() {
    // dense_data.resize(element_count);
  }

  void clear() noexcept {
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

  [[nodiscard]]
  size_t capacity() const noexcept {
    return sparse_data.size().capacity();
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

private:
  std::vector<Type> sparse_data;
  std::vector<Type> dense_data;
};

} // namespace flp
