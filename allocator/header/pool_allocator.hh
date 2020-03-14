#ifndef __POOL_ALLOCATOR_HH__
#define __POOL_ALLOCATOR_HH__

#include<mem_exceptions.hh>

namespace gsw {

/*! Creates a 'pool' of memory and allocates space from it
 *
 * @tparam T Type to allocate space for
 */
template<typename T>
class pool_allocator {
public:
  using value_type = T;
  using pointer    = value_type*;
  using reference  = value_type&;
  using size_type  = unsigned long long;

private:
  static const size_type ptrdiff = sizeof(value_type);

  size_type mIndicators;
  unsigned int mMax;
  unsigned int mSize;
  unsigned char* mPool;

public:
  /*!
   * @param count
   */
  pool_allocator(size_type count = 0)
          : mIndicators(0)
          , mMax(count)
          , mSize(0) {

    if(count <= sizeof(mIndicators) * 8) {
      mPool = new unsigned char[count * ptrdiff];
    } else {
      throw bad_alloc();
    }
  }

  pool_allocator(const pool_allocator&) = delete;

  /*!
   * @param other
   */
  pool_allocator(pool_allocator&& other) {
    delete[] mPool;

    mIndicators = other.mIndicators;
    mMax = other.mMax;
    mPool = other.mPool;

    other.mIndicators = 0;
    other.mMax = 0;
    other.mPool = nullptr;
  }

  /*!
   * @param number
   */
  pointer allocate(size_type number) {
    size_type caveStart = 0;
    size_type caveSize = 0;
    size_type index = 0;

    if(mSize + number > mMax) {
      throw bad_alloc();
    }

    for(unsigned int index = 0; index < mMax; ++index) {
      if(!(mIndicators & 1 << index)) {
        if(++caveSize == number) {
          for(unsigned int i = 0; i < number; ++i) {
            mIndicators |= (1 << (i + caveStart));
          }

          mSize += number;
          return pointer(mPool + (caveStart * ptrdiff));
        }
      } else {
        caveStart = index + 1;
        caveSize = 0;
      }
    }

    throw bad_alloc();
  }

  /*!
   * @param ptr
   *
   * @param number
   */
  void deallocate(pointer ptr, size_type number) {
    unsigned long start = ((unsigned char*) ptr - mPool) / ptrdiff;

    for(unsigned int i = 0; i < number; ++i) {
      mIndicators &= ~(1 << (i + start));
    }

    mSize -= number;
  }
};

}

#endif
