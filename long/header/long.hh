#ifndef __LONG_HH__
#define __LONG_HH__

#include<limits>

class LONG{
private:
  long long a;
  long long b;

public:
  LONG( long long ll = 0 )
    : a( 0 )
    , b( ll ){
  }

  LONG&
  operator+=( const LONG& other ){
    auto c = b;
    a += other.a;
    b += other.b;
    if( b < c || b < other.b ){
      ++a;
    }
  }

  template<typename T>
  LONG&
  operator+=( T t ){
    LONG L( t );
    (*this) += L;
    
    return *this;
  }

  LONG&
  operator-=( const LONG& other ){
    a -= other.a;
    b -= other.b;
    if( b < 0 ){
      --a;
      b += std::numeric_limits<long long>::max();
    }
  }
  
  template<typename T>
  LONG&
  operator-=( T t ){
    LONG L( t );
    (*this) -= L;

    return *this;
  }
};

#endif

