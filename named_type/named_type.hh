#ifndef __NAMED_TYPE_HH__
#define __NAMED_TYPE_HH__

namespace gsw{

template<typename T, typename parameter>
class named_type{
private:
  T mValue;

public:
  explicit
  named_type( T const & value )
    : mValue( value ){
  }
  
  explicit
  named_type( T&& value )
    : mValue( std::move( value ) ){
  }
  
  T&
  get(){
    return mValue;
  }
  
  const T&
  get() const{
    return mValue;
  }
  
  operator T() const{
    return mValue;
  }
  
  named_type&
  operator=( const named_type& name_t ){
    mValue = name_t;

    return *this;
  }
  
  named_type&
  operator=( const T& value ){
    mValue = value;

    return *this;
  }
  
  bool
  operator==( const named_type& name_t ) const{
    return mValue == name_t.mValue;
  }
  
  bool
  operator==( const T& value ) const{
    return mValue == value;
  }
};

}

#endif

