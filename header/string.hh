#ifndef __STRING_HH__
#define __STRING_HH__

/*!
 * @example test-string.cc
 */

#include<basic_string.hh>

namespace gsw{

template<>
const char basic_string<char>::terminal = '\0';

typedef basic_string<char> string;

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

