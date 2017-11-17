#ifndef __STATIC_ALLOCATOR_HH__
#define __STATIC_ALLOCATOR_HH__

#include<bitset>
#include<array>

#include<mem_exceptions.hh>

namespace gsw{

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
class static_allocator{
public:
  using value_type = T;
  using pointer    = value_type*;
  using reference  = value_type&;
  using size_type  = unsigned long long;
  static const size_type storage_size = N;

private:
  static const size_type ptrdiff = sizeof( value_type );
  static const size_type block_size = storage_size * ptrdiff;
  using ind_type = std::bitset<storage_size>;

  std::array<unsigned char, block_size> mStorage;
  ind_type mIndicator;

public:
  /*! Default ctor
   */
  static_allocator() = default;

  /*! Copy ctor
   */
  static_allocator( const static_allocator& ) = default;

  /*! Move ctor
   */
  static_allocator( static_allocator&& ) = default;

  /*!
   * @todo create subclasses of bad_alloc in order to provide values in throw statements
   */
  pointer allocate( size_type number ){
    size_type caveStart = 0;
    size_type caveSize = 0;

    if( number > ( storage_size - mIndicator.count() ) ){
      throw std::bad_alloc();
    }

    for( size_type index = 0; index < storage_size; ++index ){
      if( !mIndicator[index] ){
        if( ++caveSize == number ){
          for( size_type i = 0; i < number; ++i ){
            mIndicator.set( i + caveStart );
          }

          return pointer( mStorage.data() + ( caveStart * ptrdiff ) );
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
  void deallocate( pointer ptr, size_type number ){
    unsigned long start = ( ( unsigned char* )ptr - mStorage.data() ) / ptrdiff;

    for( unsigned int i = 0; i < number; ++i ){
      mIndicator.reset( i + start );
    }
  }

  /*!
   */
  pointer storage(){
    return pointer( mStorage.data() );
  }

  /*!
   */
  bool free_space( size_type amount = 1 ){
    return ( storage_size - mIndicator.count() ) >= amount;
  }
};

}

#endif

