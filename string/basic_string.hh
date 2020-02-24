#ifndef __BASIC_STRING_HH__
#define __BASIC_STRING_HH__

/*!
 * @example test-string.cc
 */

#include<utility>
#include<initializer_list>

#include<normal_iterator.hh>
#include<header/allocator.hh>
#include<header/allocator_traits.hh>

namespace gsw{

/*!
 * @tparam T
 *
 * @tparam ALLOC
 *
 * @todo verify msize is used correctly.  may be causing memory leak from incorrect usage
 * @todo minimize usage of terminal
 */
template<typename T, typename ALLOC = allocator<T> >
class basic_string{
public:
  /*!
   */
  using value_type = T;

  /*!
   */
  using pointer = value_type*;

  /*!
   */
  using const_pointer = const value_type*;

  /*!
   */
  using reference = value_type&;

  /*!
   */
  using const_reference = const reference;

  /*!
   */
  using size_type = unsigned long;

  /*!
   */
  using iterator = normal_iterator<value_type, basic_string>;

  /*!
   */
  using alloc = ALLOC;

private:
  using alloc_traits = allocator_traits<alloc>;

  alloc mAlloc;
  unsigned int mSize;
  pointer mString;
  static const value_type terminal;

public:
  /*! Initializer ctor
   */
  basic_string( std::initializer_list<value_type> il )
    : mSize( il.size() )
    , mString( alloc_traits::allocate( mAlloc, mSize + 1 ) ){

    unsigned int i = 0;
    for( auto el : il ){
      mString[i++] = el;
    }
  }

  /*!
   */
  basic_string( const basic_string& other )
    : mSize( other.mSize ){

    mString = alloc_traits::allocate( mAlloc, mSize + 1 );

    for( unsigned int i = 0; i <= mSize; ++i ){
      mString[i] = other.mString[i];
    }
  }

  /*!
   */
  basic_string( basic_string&& other )
    : mSize( other.mSize )
    , mString( other.mString ){
    other.mString = nullptr;
    other.mSize = 0;
  }

  /*! Default ctor
   */
  basic_string()
    : mSize( 0 )
    , mString( nullptr ){
  }

  /*! Construct from array of value_tyep
   */
  basic_string( const_pointer str )
    : mSize( 0 ){

    while( str[mSize] != terminal ){
      ++mSize;
    }

    mString = alloc_traits::allocate( mAlloc, mSize + 1 );

    mString[mSize] = terminal;
    for( unsigned int i = 0; i < mSize; ++i ){
      mString[i] = str[i];
    }
  }

  /*! Dtor
   */
  virtual
  ~basic_string(){
    alloc_traits::deallocate( mAlloc, mString, mSize + 1 );
  }

  /*! Copy assignment
   */
  basic_string&
  operator=( const basic_string& other ){
    basic_string tmp = other;

    if( mString ){
      alloc_traits::deallocate( mAlloc, mString, mSize + 1 );
    }

    *this = std::move( tmp );

    return *this;
  }

  /*! Move assignment
   */
  basic_string&
  operator=( basic_string&& other ){
    if( mString ){
      alloc_traits::deallocate( mAlloc, mString, mSize + 1 );
    }

    mSize = other.mSize;
    mString = other.mString;
    other.mSize = 0;
    other.mString = nullptr;

    return *this;
  }

  /*! String equality compare
   */
  bool
  operator==( const basic_string& other ) const{
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
  bool
  operator==( const_pointer other ) const{
    return *this == basic_string( other );
  }

  /*! Add-assign another string
   *
   * @param other
   *
   * Append other to this
   */
  basic_string&
  operator+=( const basic_string& other ){
    size_type new_size = size() + other.size();
    pointer temp_string = alloc_traits::allocate( mAlloc, new_size + 1 );

    size_type i;
    for( i = 0; i < size(); ++i ){
      temp_string[i] = mString[i];
    }
    //grab terminating character here
    for( ; i <= new_size; ++i ){
      temp_string[i] = other.mString[i - size()];
    }

    if( mString ){
      alloc_traits::deallocate( mAlloc, mString, mSize + 1 );
    }

    mString = temp_string;
    mSize = new_size;

    return *this;
  }

  /*! Add-assign array of value_type
   *
   * @param vt
   *
   * Append to this
   */
  basic_string&
  operator+=( const_pointer& vt ){
    basic_string str( vt );

    return ( *this ) += str;
  }

  /*! Concatenation
   *
   * @param lhs base being appended to
   *
   * @param rhs what to append to lhs
   */
  constexpr friend
  auto
  operator+( basic_string lhs, const basic_string& rhs ) noexcept{
    return ( lhs += rhs );
  }

  /*! Concatenation
   *
   * @param lhs base being appended to
   *
   * @param rhs what to append to lhs
   */
  constexpr friend
  auto
  operator+( basic_string lhs, const_pointer rhs ) noexcept{
    return ( lhs += rhs );
  }

  /*! Reference access
   *
   * @param idx
   */
  reference
  operator[]( unsigned int idx ){
    return mString[idx];
  }

  /*! Value access
   *
   * @param idx
   */
  const_reference
  operator[]( unsigned int idx ) const{
    return mString[idx];
  }

  /*!
   */
  size_type
  size() const{
    return mSize;
  }

  /*!
   */
  bool
  empty() const{
    return mSize == 0;
  }

  /*!
   */
  const char*
  data() const{
    return mString;
  }

  /*!
   */
  iterator
  begin(){
    return Iterator( 0 );
  }

  /*!
   */
  iterator
  end(){
    return Iterator( mSize );
  }

  /*!
   */
  iterator
  Iterator( unsigned long idx ){
    return iterator( mString + idx );
  }
};

template<typename T, typename OSTREAM>
OSTREAM&
operator<<( OSTREAM& os, const basic_string<T>& str ){
  for( unsigned int i = 0; i < str.size(); ++i ){
    os << str[i];
  }
  return os;
}

}

#endif
