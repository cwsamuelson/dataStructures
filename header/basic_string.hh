#ifndef __BASIC_STRING_HH__
#define __BASIC_STRING_HH__

/*!
 * @example test-string.cc
 */

#include<utility>
#include<initializer_list>

#include<normal_iterator.hh>

namespace gsw{

template<class T>
class basic_string{
public:
  typedef T value_type;
  typedef value_type* pointer;
  typedef const value_type* const_pointer;
  typedef value_type& reference;
  typedef const reference const_reference;
  typedef unsigned long size_type;
  typedef normal_iterator<value_type, basic_string> iterator;

private:
  unsigned int mSize;
  pointer mString;
  static const value_type terminal;

public:
  basic_string( std::initializer_list<value_type> il ):
    mSize( il.size() ),
    mString( new value_type[mSize + 1] ){

    unsigned int i = 0;
    for( auto el : il ){
      mString[i++] = el;
    }
  }
  template<typename U>
  basic_string( U&& other ):
    mSize( 0 ),
    mString( nullptr ){
    *this = std::forward<U>( other );
  }
  basic_string():
    mSize( 0 ),
    mString( nullptr ){
  }
  basic_string( const_pointer str ):
    mSize( 0 ){

    while( str[mSize] != terminal ){
      ++mSize;
    }

    mString = new value_type[mSize + 1];

    mString[mSize] = terminal;
    for( unsigned int i = 0; i < mSize; ++i ){
      mString[i] = str[i];
    }
  }
  virtual ~basic_string(){
    delete[] mString;
  }
  
  basic_string& operator=( const basic_string& other ){
    if( mString ){
      delete[] mString;
    }

    mSize = other.mSize;
    
    mString = new value_type[mSize + 1];
    mString[mSize] = terminal;

    for( unsigned int i = 0; i < mSize; ++i ){
      mString[i] = other.mString[i];
    }
    
    return *this;
  }
  basic_string& operator=( basic_string&& other ){
    mSize = other.mSize;
    mString = other.mString;
    other.mSize = 0;
    other.mString = nullptr;
    
    return *this;
  }

  bool operator==( const basic_string& other ) const{
    if( mSize != other.mSize ){
      return false;
    }
    
    bool ret = true;
    
    for( unsigned int i = 0; i < mSize; ++i ){
      ret &= ( mString[i] == other.mString[i] );
    }
    return ret;
  }
  bool operator==( const_pointer other ) const{
    return *this == basic_string( other );
  }

  basic_string operator+( const_reference vt ) const{
    basic_string ret;

    ret.mSize = mSize + 1;
    ret.mString = new value_type[ret.mSize + 1];
    ret.mString[ret.mSize] = terminal;

    for( unsigned int i = 0; i < mSize; ++i ){
      ret.mString[i] = mString[i];
    }
    ret.mString[mSize] = vt;

    return ret;
  }
  basic_string operator+( const_pointer ptr ){
    size_type extra = 0;
    basic_string ret;

    while( ptr[extra] != terminal ){
      ++extra;
    }

    ret.mSize = mSize + extra;
    ret.mString = new value_type[ret.mSize + 1];
    ret.mString[ret.mSize] = terminal;

    for( unsigned int i = 0; i < mSize; ++i ){
      ret.mString[i] = mString[i];
    }
    for( unsigned int i = 0; i < extra; ++i ){
      ret.mString[i + mSize] = ptr[i];
    }

    return ret;
  }
  template<class U>
  basic_string operator+( U u ){
    return ( *this ) + value_type( u );
  }
  basic_string& operator+=( const_reference ref ){
    return ( ( *this ) = ( *this ) + ref );
  }
  basic_string& operator+=( const_pointer ptr ){
    return ( ( *this ) = ( *this ) + ptr );
  }
  template<class U>
  basic_string& operator+=( U u ){
    return ( ( *this ) = ( *this ) + u );
  }

  reference operator[]( unsigned int idx ){
    return mString[idx];
  }
  const_reference operator[]( unsigned int idx ) const{
    return mString[idx];
  }
  size_type size() const{
    return mSize;
  }
  bool empty() const{
    return mSize == 0;
  }
  const char* data() const{
    return mString;
  }

  iterator begin(){
    return Iterator( 0 );
  }
  iterator end(){
    return Iterator( mSize );
  }
  iterator Iterator( unsigned long idx ){
    return iterator( mString + idx );
  }
};

template<class T, typename OSTREAM>
OSTREAM& operator<<( OSTREAM& os, const basic_string<T>& str ){
  for( unsigned int i = 0; i < str.size(); ++i ){
    os << str[i];
  }
  return os;
}

class test_ct_string{
private:
  const char* const mString;
  const size_t mSize;

public:
  template<size_t N>
  constexpr test_ct_string( const char( &a )[N] ):
    mString( a ),
    mSize( N - 1 ){
  }

  constexpr char operator[]( size_t n ) const{
    return n < mSize ? mString[n] : throw 1;
  }

  constexpr size_t size() const{
    return mSize;
  }
};

template<char ...STRING>
struct ct_string{
  static basic_string<char> string(){
    return basic_string<char>{ STRING... };
  }
};

template<typename L, typename R>
struct concatenate;

template<char ...Ls, char ...Rs>
struct concatenate<ct_string<Ls...>, ct_string<Rs...> >{
  using result = ct_string<Ls..., Rs...>;
};

}

#endif

