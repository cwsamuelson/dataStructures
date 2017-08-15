#ifndef __BASIC_STRING_HH__
#define __BASIC_STRING_HH__

/*!
 * @example test-string.cc
 */

#include<utility>
#include<initializer_list>

#include<normal_iterator.hh>

namespace gsw{

/*!
 * @tparam T
 *
 * @todo verify msize is used correctly.  may be causing memory leak from incorrect usage
 * @todo minimize usage of terminal
 */
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
  /*! Initializer ctor
   */
  basic_string( std::initializer_list<value_type> il ):
    mSize( il.size() ),
    mString( new value_type[mSize + 1] ){

    unsigned int i = 0;
    for( auto el : il ){
      mString[i++] = el;
    }
  }

  /*!
   */
  template<typename U>
  basic_string( U&& other ):
    mSize( 0 ),
    mString( nullptr ){
    *this = std::forward<U>( other );
  }

  /*! Default ctor
   */
  basic_string():
    mSize( 0 ),
    mString( nullptr ){
  }

  /*! Construct from array of value_tyep
   */
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

  /*! Dtor
   */
  virtual ~basic_string(){
    delete[] mString;
  }
  
  /*! Copy assignment
   */
  basic_string& operator=( const basic_string& other ){
    if( mString ){
      delete[] mString;
    }

    mSize = other.mSize;
    
    mString = new value_type[mSize + 1];

    // be sure to include terminator (so use <= )
    for( unsigned int i = 0; i <= mSize; ++i ){
      mString[i] = other.mString[i];
    }
    
    return *this;
  }

  /*! Move assignment
   */
  basic_string& operator=( basic_string&& other ){
    mSize = other.mSize;
    mString = other.mString;
    other.mSize = 0;
    other.mString = nullptr;
    
    return *this;
  }

  /*! String equality compare
   */
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

  /*! Equality compare against array of value_type
   */
  bool operator==( const_pointer other ) const{
    return *this == basic_string( other );
  }

  /*! Add-assign another string
   *
   * @param other
   *
   * Append other to this
   */
  basic_string operator+=( const basic_string& other ){
    size_type new_size = size() + other.size();
    pointer temp_string = new value_type[new_size + 1];

    size_type i;
    for( i = 0; i < size(); ++i ){
      temp_string[i] = mString[i];
    }
    //grab terminating character here
    for( ; i <= new_size; ++i ){
      temp_string[i] = other.mString[i - size()];
    }
  }

  /*! Add-assign array of value_type
   *
   * @param vt
   *
   * Append to this
   */
  basic_string operator+=( const_pointer& vt ){
    basic_string str( vt );

    return ( *this ) += str;
  }

  /*! Concatenation
   *
   * @param lhs base being appended to
   *
   * @param rhs what to append to lhs
   */
  constexpr friend auto operator+( basic_string lhs, const basic_string& rhs ) noexcept{
    return ( lhs += rhs );
  }

  /*! Concatenation
   *
   * @param lhs base being appended to
   *
   * @param rhs what to append to lhs
   */
  constexpr friend auto operator+( basic_string lhs, const_pointer rhs ) noexcept{
    return ( lhs += rhs );
  }

  /*! Reference access
   *
   * @param idx
   */
  reference operator[]( unsigned int idx ){
    return mString[idx];
  }

  /*! Value access
   *
   * @param idx
   */
  const_reference operator[]( unsigned int idx ) const{
    return mString[idx];
  }

  /*!
   */
  size_type size() const{
    return mSize;
  }

  /*!
   */
  bool empty() const{
    return mSize == 0;
  }

  /*!
   */
  const char* data() const{
    return mString;
  }

  /*!
   */
  iterator begin(){
    return Iterator( 0 );
  }

  /*!
   */
  iterator end(){
    return Iterator( mSize );
  }

  /*!
   */
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
  constexpr test_ct_string( const char( &arr )[N] ):
    mString( arr ),
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

