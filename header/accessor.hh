#ifndef __ACCESSOR_HH__
#define __ACCESSOR_HH__

template<typename T>
class accessor{
public:
  typedef T value_type;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef function<void(T)> callback;

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
    mRef = cref;
    mcb( cref );
  }
};

#endif

