#ifndef __SHARED_PTR_HH__
#define __SHARED_PTR_HH__

#include<utility>

/*!
 * @example test-shared.cc
 */

namespace gsw {

/*! Shared pointer class
 *
 * @tparam T Type of object pointer points to
 *
 * Class to model a pointer that has multiple 'owners'.  When no more owners
 * exist, object cleans itself up.
 */
template<typename T>
class shared_ptr {
public:
  using value_type = T;
  using pointer = value_type*;
  using reference = value_type&;
  using count_t = unsigned long;

private:
  pointer mData;
  count_t* mCount;

public:
  /*! basic ctor
   */
  shared_ptr()
          : mData(nullptr)
          , mCount(nullptr) {
  }

  /*! Ownership ctor
   *
   * @param ptr Pointer to be taken ownership of
   *
   * This constructor takes initial ownership of a provided pointer
   */
  shared_ptr(pointer ptr)
          : mData(ptr) {
    if(mData != nullptr) {
      mCount = new count_t(1);
    } else {
      mCount = nullptr;
    }
  }

  /*! Copy ctor
   *
   * @param other shared_ptr to copy
   *
   * The provided shared_ptr is copied, increasing the owner count
   */
  shared_ptr(const shared_ptr& other)
          : mData(other.mData)
          , mCount(other.mCount) {
    ++(*mCount);
  }

  /*! Move ctor
   *
   * @param other Pointer to take ownership from
   *
   * Takes ownership of pointer from other.
   */
  shared_ptr(shared_ptr&& other)
          : mData(other.mData)
          , mCount(other.mCount) {

    other.mData = nullptr;
    other.mCount = nullptr;
  }

  /*! destructor
   */
  virtual
  ~shared_ptr() {
    if((mCount != nullptr) && (--(*mCount) == 0)) {
      delete mData;
      delete mCount;
    }
  }

  /*! Ownership assignment
   *
   * @param other Pointer to be taken ownership of
   *
   * This constructor takes initial ownership of a provided pointer
   */
  shared_ptr& operator=(pointer other) {
    if(mData != other) {
      if((mCount != nullptr) && (--(*mCount) == 0)) {
        delete mData;
        delete mCount;
      }
      mData = other;
      mCount = new count_t(1);
    }
    return *this;
  }

  /*! Copy assignment
   *
   * @param other shared_ptr to copy
   *
   * The provided shared_ptr is copied, increasing the owner count
   */
  shared_ptr& operator=(shared_ptr& other) {
    if(mData != other.mData) {
      if(--(*mCount) == 0) {
        delete mData;
        delete mCount;
      }
      mData = other.mData;
      mCount = other.mCount;
      ++(*mCount);
    }
    return *this;
  }

  /*! Move assignment
   *
   * @param other Pointer to take ownership from
   *
   * Takes ownership of pointer from other.
   */
  shared_ptr& operator=(shared_ptr&& other) {
    // cleanup current storage
    if(mCount != nullptr) {
      --(*mCount);
      if(*mCount == 0) {
        delete mData;
        delete mCount;
      }
    }

    //take on new storage
    mData = other.mData;
    mCount = other.mCount;

    //obliterate old storage
    other.mData = nullptr;
    other.mCount = nullptr;

    return *this;
  }

  /*! equality operator
   *
   * @param other pointer to compare against
   *
   * Compares provided pointer against stored pointer
   */
  bool operator==(pointer other) const {
    return mData == other;
  }

  /*! equality operator
   *
   * @param other shared_ptr to compare against
   *
   * Compares shared_ptrs
   */
  bool operator==(const shared_ptr& other) const {
    return (mData == other.mData) && (mCount == other.mCount);
  }

  /*! Dereference operator
   *
   * Returns reference to stored object
   */
  reference operator*() {
    return *mData;
  }

  /*! Class member access operator
   *
   * Enables member access of stored object
   *
   * struct type{
   *   int i;
   * };
   *
   * shared_ptr<type> sp( new type );
   *
   * sp->i = 3;
   */
  pointer operator->() {
    return mData;
  }
};

/*! Shared_ptr factory method
 *
 * @tparam T Type of created pointer
 *
 * @tparam ...Args Types of arguments to be given to new object instance
 *
 * @param ...args Arguments to be forwarded to objects constructor
 */
template<typename T, typename ...Args>
shared_ptr<T> make_shared(Args&& ... args) {
  return shared_ptr<T>(new T(std::forward<Args>(args)...));
}

}

#endif
