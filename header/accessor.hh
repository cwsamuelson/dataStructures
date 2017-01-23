#ifndef __ACCESSOR_HH__
#define __ACCESSOR_HH__

#include<functional>

template<typename T>
class accessor{
public:
  typedef T value_type;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef std::function<bool(value_type)> callback;

private:
  reference mRef;
  callback mcb;

public:
  accessor( reference r, callback cb ):
    mRef( r ),
    mcb( cb ){
  }

  operator value_type(){
    return mRef;
  }

  reference operator=( const_reference cref ){
    if( mcb( cref ) ){
      mRef = cref;
    }
    return mRef;
  }
  reference operator=( value_type&& other ){
    if( mcb( other ) ){
      mRef = std::forward<value_type>( other );
    }
    return mRef;
  }

  bool operator==( const_reference cref ){
    return mRef == cref;
  }
};

#endif

