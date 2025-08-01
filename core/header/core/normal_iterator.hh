#pragma once

#include<iterator>

#include"additive.hh"

namespace flp {

template<typename Type, typename CONTAINER, typename PTR_T = Type*>
class normal_iterator : public additive<normal_iterator<Type, CONTAINER>, long long> {
public:
  using container = CONTAINER;
  using value_type = Type;
  using pointer = PTR_T;
  using reference = value_type&;

  template<typename T1, typename C1, typename P1>
  friend
  class normal_iterator;

protected:
  pointer mCurrent = nullptr;

public:
  normal_iterator() noexcept = default;
  explicit normal_iterator(pointer ptr) noexcept
    : mCurrent(ptr)
  {}
  explicit normal_iterator(std::nullptr_t) noexcept
    : normal_iterator()
  {}

  template<typename T1, typename C1, typename P1>
  normal_iterator(const normal_iterator<T1, C1, P1>& iter)
    : mCurrent(iter.mCurrent) {
  }

  [[nodiscard]]
  unsigned int operator-(const normal_iterator& other) const {
    return mCurrent - other.mCurrent;
  }

  normal_iterator& operator+=(long long mod) {
    mCurrent += mod;
    return *this;
  }

  normal_iterator& operator-=(long long mod) {
    mCurrent -= mod;
    return *this;
  }

  [[nodiscard]]
  friend bool operator==(const normal_iterator&, const normal_iterator&) noexcept = default;

  [[nodiscard]]
  friend auto operator<=>(const normal_iterator&, const normal_iterator&) noexcept = default;

  [[nodiscard]]
  reference operator*() const {
    return *mCurrent;
  }

  [[nodiscard]]
  pointer operator->() const {
    return mCurrent;
  }

  normal_iterator& operator++() {
    ++mCurrent;
    return *this;
  }

  normal_iterator operator++(int) {
    return normal_iterator(mCurrent++);
  }

  normal_iterator& operator--() {
    --mCurrent;
    return *this;
  }

  normal_iterator operator--(int) {
    return normal_iterator(mCurrent--);
  }
};

}

namespace std {

template<typename Type, typename CONTAINER>
struct iterator_traits<flp::normal_iterator<Type, CONTAINER>> {
public:
  using value_type = typename flp::normal_iterator<Type, CONTAINER>::value_type;
  using difference_type = unsigned int;
  using iterator_category = random_access_iterator_tag;
};

}

