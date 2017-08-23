#ifndef __POOL_ALLOCATOR_HH__
#define __POOL_ALLOCATOR_HH__

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
    pool( new char[sizeof( mIndicators ) * 8 * ptrdiff] ){
  }

  allocator( const allocator& ){
  }

  allocator( allocator&& other ){
    delete[] pool;

    pool = other.pool;
    mIndicators = other.mIndicators;

    other.pool = nullptr;
    other.mIndicators = 0;
  }

  pointer allocate( size_type number ){
    size_type mask = 1;

    for( unsigned int i = 0; i < sizeof
  }

  void deallocate( pointer ptr ){
  }
};

#endif

