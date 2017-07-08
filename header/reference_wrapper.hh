#ifndef __REFERENCE_WRAPPER_HH__
#define __REFERENCE_WRAPPER_HH__

/*!
 * @example test-wrapper.cc
 */

namespace gsw{

template<typename T>
class reference_wrapper{
public:
  typedef T value_type;
  typedef value_type& reference;
  typedef const value_type& const_ref;

private:
  reference mRef;

public:
  reference_wrapper( reference ref ):
    mRef( ref ){
  }

  operator reference(){
    return mRef;
  }
  reference get(){
    return mRef;
  }
  const reference get() const{
    return mRef;
  }
};

}

#endif

