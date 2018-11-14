#ifndef __STRING_HH__
#define __STRING_HH__

/*!
 * @example test-string.cc
 */

#include<stdexcept>

#include<basic_string.hh>

namespace gsw{

template<>
const char basic_string<char>::terminal = '\0';

using string = basic_string<char>;

/*!
 */
class test_ct_string{
private:
  const char* const mString;
  const size_t mSize;

public:
  /*!
   */
  template<size_t N>
  constexpr
  test_ct_string( const char( &arr )[N] )
    : mString( arr )
    , mSize( N - 1 ){
  }

  /*!
   */
  constexpr
  char
  operator[]( size_t n ) const{
    if( n < mSize ){
      return mString[n];
    } else {
      throw std::out_of_range( "Supplied value is out of range" );
    }
  }

  /*!
   */
  constexpr
  size_t
  size() const{
    return mSize;
  }

  /*!
   */
  constexpr
  bool
  operator==( const test_ct_string& other ) const{
    if( mSize != other.mSize ){
      return false;
    }

    for( size_t i = 0; i < mSize; ++i ){
      if( mString[i] != other.mString[i] ){
        return false;
      }
    }

    return true;
  }

  /*!
   */
  constexpr
  bool
  operator!=( const test_ct_string& other ) const{
    return !( *this == other );
  }
};

/*! Compile time string
 *
 * @tparam STRING List of characters comprising the string
 */
template<char ...STRING>
struct ct_string{
  /*! Retrieve compile time string at runtime
   */
  static
  basic_string<char>
  string(){
    return basic_string<char>{ STRING... };
  }

  /*! Compare with another string
   *
   * Equality is determined at compile time because the types are the same,
   * indicating the content is the same as well.
   */
  constexpr
  bool
  operator==( const ct_string& ) const{
    return true;
  }

  /*! Compare with another string
   *
   * @tparam OTHER_STRING
   *
   * Since this function was deduced, and not the previous overload, then the
   * string content is different
   */
  template<char ...OTHER_STRING>
  constexpr
  bool
  operator==( const ct_string<OTHER_STRING...>& ) const{
    return false;
  }

  /*!
   */
  template<char ...OTHER_STRING>
  constexpr
  bool
  operator!=( const ct_string<OTHER_STRING...>& other ) const{
    return !( *this == other );
  }
};

template<typename L, typename R>
struct concatenate;

/*! Concatenate two ct_strings together
 *
 * @tparam Ls... Lefthand side string characters
 *
 * @tparam Rs... Righthand side string characters
 *
 * @code{.cpp}
 * ct_string<'h'> h;
 * ct_string<'i'> i;
 *
 * assert( concatenate<h, i>::result == ct_string<'h', 'i'> );
 * @endcode
 */
template<char ...Ls, char ...Rs>
struct concatenate<ct_string<Ls...>, ct_string<Rs...> >{
  /*! Result of the concatenation
   */
  using result = ct_string<Ls..., Rs...>;
};

/*!
 */
template<char ...Ls, char ...Rs>
constexpr
auto
cat( ct_string<Ls...>, ct_string<Rs...> ){
  return ct_string<Ls..., Rs...>();
}

}

#endif
