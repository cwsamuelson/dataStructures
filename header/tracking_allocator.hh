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
  static size_type mMaxStored;
  static size_type mCurrentStored;

public:
  /*! Update tracking data, call base allocation
   *
   * @return Pointer to newly allocated objects
   */
  pointer
  allocate( size_type number ){
    mCurrentStored += number;

    mMaxStored = std::max( mMaxStored, mCurrentStored );

    return base::allocate( number );
  }

  /*! Update tracking data, call base deallocation
   */
  void
  deallocate( pointer ptr, size_type number ){
    mCurrentStored -= number;

    base::deallocate( ptr, number );
  }

  /*! Get the current number of T objects
   *
   * @return The current usage value
   */
  size_type
  usage() const{
    return mCurrentStored;
  }

  /*! Get the max usage thus far
   *
   * @return The maximum usage value
   *
   * Maximum number of objects of type T allocated at one time
   */
  size_type
  max_usage() const{
    return mMaxStored;
  }
};

template<typename T, typename A>
typename tracking_allocator<T, A>::size_type tracking_allocator<T, A>::mMaxStored = 0;
template<typename T, typename A>
typename tracking_allocator<T, A>::size_type tracking_allocator<T, A>::mCurrentStored = 0;

}

#endif
