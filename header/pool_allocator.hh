#ifndef __POOL_ALLOCATOR_HH__
#define __POOL_ALLOCATOR_HH__

#include<exception>

namespace gsw{

class bad_alloc : public std::exception{
public:
  virtual const char* what() const noexcept{
    return "Bad allocation!";
  }
};

template<typename T>
class pool_allocator{
public:
  using value_type = T;
  using pointer    = value_type*;
  using reference  = value_type&;
  using size_type  = unsigned long long;

private:
  static const size_type ptrdiff = sizeof( value_type );
  size_type mIndicators;
  char* pool;

public:
  allocator():
    mIndicators( 0 ),
    pool( new char[sizeof( mIndicators ) * 8 * ptrdiff] ){
  }

  allocator( const allocator& ) = delete;

  allocator( allocator&& other ){
    delete[] pool;

    pool = other.pool;
    mIndicators = other.mIndicators;

    other.pool = nullptr;
    other.mIndicators = 0;
  }

  pointer allocate( size_type number ){
    int caveSize = 0;
    int index = 0;

    for( unsigned int index = 0; index < sizeof( mIndicators ) * 8 ){
      if( !( mIndicators & 1 << index ) ){
        ++caveSize;

        if( caveSize == number ){
          for( unsigned int i = 0; i < number; ++i ){
            mIndicators |= ( 1 << ( i + index ) );
          }

          return pool + ( index * ptrdiff );
        }
      }

      ++index;
    }

    throw bad_alloc();
  }

  void deallocate( pointer ptr, size_type number ){
    unsigned long start = ( ptr - pool ) / ptrdiff;

    for( unsigned int i = 0; i < number; ++i ){
      mIndicators &= ~( 1 << ( i + start ) );
    }
  }
};

}

#endif

