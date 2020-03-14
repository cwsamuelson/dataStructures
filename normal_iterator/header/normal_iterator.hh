#ifndef __NORMAL_ITERATOR_HH__
#define __NORMAL_ITERATOR_HH__

#include<iterator>

#include"additive.hh"

namespace gsw {

/*! Normalized iterator
 *
 * @tparam TYPE
 *
 * @tparam CONTAINER
 */
template<typename TYPE, typename CONTAINER, typename PTR_T = TYPE*>
class normal_iterator : public additive<normal_iterator<TYPE, CONTAINER>, long long> {
public:
  using container = CONTAINER;
  using value_type = TYPE;
  using pointer = PTR_T;
  using reference = value_type&;

  template<typename T1, typename C1, typename P1> friend
  class normal_iterator;

protected:
  pointer mCurrent;

public:
  /*!
   * @param ptr
   *
   */
  normal_iterator(pointer ptr)
          : mCurrent(ptr) {
  }

  /*!
   * @tparam T1
   *
   * @tparam C1
   *
   * @tparam P1
   *
   * @param iter
   *
   * @todo verify if making this ctor a template could cause issues
   * this was made a template for use in map, allowing a vector (actual storage
   * type) iterator to be converted to a map iterator for external usage.
   * However, allowing iterators to convert between iterator types could be an
   * issue, and is probably something to be guarded against.
   */
  template<typename T1, typename C1, typename P1>
  normal_iterator(const normal_iterator<T1, C1, P1>& iter)
          : mCurrent(iter.mCurrent) {
  }

  /*!
   * @param other
   */
  unsigned int operator-(const normal_iterator& other) const {
    return mCurrent - other.mCurrent;
  }

  /*!
   * @param mod
   */
  normal_iterator& operator+=(long long mod) {
    mCurrent += mod;
    return *this;
  }

  /*!
   * @param mod
   */
  normal_iterator& operator-=(long long mod) {
    mCurrent -= mod;
    return *this;
  }

  /*!
   * @param iter
   */
  bool operator==(const normal_iterator& iter) const {
    return mCurrent == iter.mCurrent;
  }

  /*!
   * @param iter
   */
  bool operator!=(const normal_iterator& iter) const {
    return !((*this) == iter);
  }

  /*!
   * @param other
   */
  bool operator<(const normal_iterator& other) const {
    return mCurrent < other.mCurrent;
  }

  /*!
   * @param other
   */
  bool operator>(const normal_iterator& other) const {
    return mCurrent > other.mCurrent;
  }

  /*!
   *
   */
  reference operator*() const {
    return *mCurrent;
  }

  /*!
   *
   */
  pointer operator->() const {
    return mCurrent;
  }

  /*!
   *
   */
  normal_iterator& operator++() {
    ++mCurrent;
    return *this;
  }

  /*!
   *
   */
  normal_iterator operator++(int) {
    return normal_iterator(mCurrent++);
  }

  /*!
   *
   */
  normal_iterator& operator--() {
    --mCurrent;
    return *this;
  }

  /*!
   *
   */
  normal_iterator operator--(int) {
    return normal_iterator(mCurrent--);
  }
};

}

namespace std {

template<typename TYPE, typename CONTAINER>
struct iterator_traits<gsw::normal_iterator<TYPE, CONTAINER>> {
public:
  typedef typename gsw::normal_iterator<TYPE, CONTAINER>::value_type value_type;
  typedef unsigned int difference_type;
  typedef random_access_iterator_tag iterator_category;
};

}

#endif
