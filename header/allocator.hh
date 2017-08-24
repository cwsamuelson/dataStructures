#ifndef __ALLOCATOR_HH__
#define __ALLOCATOR_HH__

namespace gsw{

template<typename T>
class allocator{
public:
  using value_type = T;
  using pointer    = value_type*;
  using reference  = value_type&;
  using size_type  = unsigned long;

private:

public:
  allocator() = default;
  allocator( const allocator& ) = default;
  allocator( allocator&& ) = default;

  pointer allocate( size_type number ){
    return pointer( new unsigned char[number * sizeof( value_type )] );
  }

  void deallocate( pointer ptr, size_type number ){
    ( void )number;
    delete[] ( unsigned char* )( ptr );
  }
};

}

#endif

