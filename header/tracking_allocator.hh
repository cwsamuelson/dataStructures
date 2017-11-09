#ifndef __TRACKING_ALLOCATOR_HH__
#define __TRACKING_ALLOCATOR_HH__

#include<algorithm>

#include<allocator.hh>

namespace gsw{

template<typename T, typename A = allocator<T> >
class tracking_allocator : public A{
public:
  using value_type = T;
  using pointer    = value_type*;
  using reference  = value_type&;
  using size_type  = unsigned long;
  using base       = A;

private:
  static size_type mMaxStored = 0;
  static size_type mCurrentStored = 0;

public:
  pointer allocate( size_type number ){
    mCurrentStored += number;

    mMaxStored = std::max( mMaxStored, mCurrentStored );

    base::allocate( number );
  }

  using base::deallocate;
};

}

#endif

