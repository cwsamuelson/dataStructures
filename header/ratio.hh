#ifndef __RATIO_HH__
#define __RATIO_HH__

#include<numeric>

template<typename T>
constexpr signed int sign( T t ){
  if( std::signbit( t ) ){
    return -1;
  } else {
    return 1;
  }
}

template<typename T>
constexpr T myAbs( T t ){
  if( t < 0 ){
    return -t;
  } else {
    return t;
  }
}

template<typename T, typename U>
constexpr std::common_type_t<T, U> gcd( T t, U u ){
  //return std::gcd( t, u );
  while ( u != 0 ){
    unsigned r = t % u;

    t = u;
    u = r;
  }

  return t;
}

template<size_t N, size_t D>
class ratio{
public:
  typedef size_t value_type;
  static const value_type numerator = sign( N ) * sign( D ) * myAbs( N ) / gcd( N, D );
  static const value_type denominator = myAbs( D ) / gcd( N, D );
  static constexpr double value = double( double( numerator ) / double( denominator ) );
  typedef ratio<numerator, denominator> type;

  constexpr operator double() const{
    return value;
  }

  template<size_t NUM, size_t DEN>
  constexpr auto operator*( ratio<NUM, DEN> other ){
    typedef decltype( other ) OTHER;

    return ratio<numerator * OTHER::numerator, denominator * OTHER::denominator>();
  }
  template<size_t NUM, size_t DEN>
  constexpr auto operator/( ratio<NUM, DEN> other ){
    typedef decltype( other ) OTHER;

    return ratio<numerator * OTHER::denominator, denominator * OTHER::numerator>();
  }
};

template<typename T, size_t N, size_t D>
T operator*( T t, ratio<N, D> r ){
  return t * double( r );
}
template<typename T, size_t N, size_t D>
T operator*( ratio<N, D> r, T t ){
  return t * double( r );
}

template<typename T, size_t N, size_t D>
T operator/( T t, ratio<N, D> r ){
  return t / double( r );
}
template<typename T, size_t N, size_t D>
T operator/( ratio<N, D> r, T t ){
  return t / double( r );
}

template<size_t N1, size_t D1,
         size_t N2, size_t D2>
constexpr bool operator==( ratio<N1, D1> r1, ratio<N2, D2> r2 ){
  typedef decltype( r1 ) R1;
  typedef decltype( r2 ) R2;

  return R1::value == R2::value;
}
template<size_t N1, size_t D1,
         size_t N2, size_t D2>
constexpr bool operator!=( ratio<N1, D1> r1, ratio<N2, D2> r2 ){
  return ! ( r1 == r2 );
}

//This declaration prevents a linker error
template<size_t N, size_t D>
constexpr double ratio<N, D>::value;

#endif

