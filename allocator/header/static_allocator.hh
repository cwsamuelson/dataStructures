#ifndef __STATIC_ALLOCATOR_HH__
#define __STATIC_ALLOCATOR_HH__

#include<bitset>
#include<array>

#include<mem_exceptions.hh>

namespace gsw {

/* In research for stateful allocators, I found this:
  Do you have any suggestions for how to do the sort of thing I'm trying to do? That is, how do I include
  allocated-type-specific state in my allocator?

  Don't embed it directly in the allocator, store it separately and have the allocator refer to it by a pointer
  (possibly smart pointer, depending on how you design the lifetime management of the resource). The actual allocator
  object should be a lightweight handle on to some external source of memory (e.g. an arena, or pool, or something
  managing a freelist). Allocator objects that share the same source should compare equal, this is true even for
  allocators with different value types (see below).

  https://stackoverflow.com/questions/24278803/how-can-i-write-a-stateful-allocator-in-c11-given-requirements-on-copy-constr

  This should probably be taken under advisement, but indicates a different structure than what has been previously assumed.
  Previously:
  allocator<T> a;
  container1<T, allocator<T> > c1( a );
  container2<T, allocator<T> > c2( a );

  A better solution may be to create a memory store object, and allow allocators to use it?
  store s( store_size );
  container<T, allocator<T> > c1( allocator<T>( s ) );
  */

/*! Uses stack space to allocate from
 *
 * @tparam T Type of objects to allocate space for
 *
 * @tparam N How many objects can be allocated (how many to create space for)
 *
 * Of course if this allocator is created on the heap, the memory will actually
 * pull from the heap.  However the memory used is in a local array, so by
 * creating this allocator, all memory that can be retrieved from this
 * allocator is already set aside, meaning allocation cannot fail unless an
 * allocation request is made in excess of N.
 */
template<typename T, size_t N>
class static_allocator {
public:
  using value_type = T;
  using pointer    = value_type*;
  using reference  = value_type&;
  using size_type  = unsigned long long;

  static const size_type storage_size = N;

private:
  static const size_type ptrdiff = sizeof(value_type);

  static const size_type block_size = storage_size * ptrdiff;

  using ind_type = std::bitset<storage_size>;

  std::array<unsigned char, block_size> mStorage;
  ind_type mIndicator;

public:
  static_allocator() = default;
  static_allocator(const static_allocator&) = default;
  static_allocator(static_allocator&&) noexcept = default;

  /*!
   * @todo create subclasses of bad_alloc in order to provide values in throw statements
   */
  [[nodiscard]]
  pointer allocate(size_type number) {
    size_type caveStart = 0;
    size_type caveSize = 0;

    if(number > (storage_size - mIndicator.count())) {
      throw std::bad_alloc();
    }

    for(size_type index = 0; index < storage_size; ++index) {
      if(!mIndicator[index]) {
        if(++caveSize == number) {
          for(size_type i = 0; i < number; ++i) {
            mIndicator.set(i + caveStart);
          }

          return pointer(mStorage.data() + (caveStart * ptrdiff));
        }
      } else {
        caveStart = index + 1;
        caveSize = 0;
      }
    }

    throw std::bad_alloc();
  }

  /*!
   */
  void deallocate(pointer ptr, size_type number) {
    unsigned long start = ((unsigned char*) ptr - mStorage.data()) / ptrdiff;

    for(unsigned int i = 0; i < number; ++i) {
      mIndicator.reset(i + start);
    }
  }

  /*!
   */
  [[nodiscard]]
  pointer storage() {
    return pointer(mStorage.data());
  }

  /*!
   */
  [[nodiscard]]
  bool free_space(size_type amount = 1) {
    return (storage_size - mIndicator.count()) >= amount;
  }
};

}

#endif
