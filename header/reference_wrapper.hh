#ifndef __REFERENCE_WRAPPER_HH__
#define __REFERENCE_WRAPPER_HH__

template<typename T>
class reference_wrapper{
public:
  typedef T value_type;
  typedef value_type& reference;

private:
  reference mRef;

public:
  reference_wrapper( reference ref ):
    mRef( ref ){
  }

  operator reference(){
    return mRef;
  }
  operator const reference(){
    return mRef;
  }

  reference get(){
    return mRef;
  }
  const reference get() const{
    return mRef;
  }
};

#endif

