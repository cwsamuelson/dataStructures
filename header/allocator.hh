#ifndef __ALLOCATOR_HH__
#define __ALLOCATOR_HH__

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
    return new value_type[number];
  }

  void deallocate( pointer ptr ){
    delete[] ptr;
  }
};

#endif

