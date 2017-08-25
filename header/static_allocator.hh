#ifndef __STATIC_ALLOCATOR_HH__
#define __STATIC_ALLOCATOR_HH__

#include<bitset>
#include<array>

#include<mem_exceptions.hh>

namespace gsw{

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
  using ind_type = std::bitset<storage_size>;
  std::array<unsigned char, storage_size * sizeof( value_type)> mStorage;
  ind_type mIndicator;

public:
  static_allocator() = default;

  static_allocator( const static_allocator& ) = default;

  static_allocator( static_allocator&& ) = default;

  pointer allocate( size_type number ){
    size_type caveStart = 0;
    size_type caveSize = 0;
    size_type index = 0;

    if( number > ( storage_size - mIndicator.count() ) ){
      throw bad_alloc();
    }

    for( unsigned int index = 0; index < storage_size; ++index ){
      if( !mIndicator[index] ){
        if( ++caveSize == number ){
          for( unsigned int i = 0; i < number; ++i ){
            mIndicator.set( i + caveStart );
          }

          return pointer( mStorage.data() + ( caveStart * ptrdiff ) );
        }
      } else {
        caveStart = index + 1;
        caveSize = 0;
      }
    }

    throw bad_alloc();
  }

  void deallocate( pointer ptr, size_type number ){
    unsigned long start = ( ( unsigned char* )ptr - mStorage.data() ) / ptrdiff;

    for( unsigned int i = 0; i < number; ++i ){
      mIndicator.reset( i + start );
    }
  }
};

}

#endif

