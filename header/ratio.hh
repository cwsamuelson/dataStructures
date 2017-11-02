#ifndef __RATIO_HH__
#define __RATIO_HH__

/*!
 * @example test-ratio.cc
 */

#include<numeric>
#include<type_traits>

namespace gsw{

/*! Get the sign of a given number
 *
 * @tparam T  Type of provided argument
 *
 * @param t  Integral argument
 */
template<typename T>
constexpr signed int sign( T t ){
  if( std::signbit( t ) ){
    return -1;
  } else {
    return 1;
  }
}

/*! Get the absolute value of a given number
 *
 * @tparam T  Type of provided argument
 *
 * @param t  Numeric argument
 */
template<typename T>
constexpr T myAbs( T t ){
  if( t < 0 ){
    return -t;
  } else {
    return t;
  }
}

/*! Get the greatest common denominator of 2 values
 *
 * @tparam T  Type of 'lhs'
 *
 * @tparam U  Type of 'rhs'
 */
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

/*! Compile time integer ratio class
 *
 * @tparam N  Numerator value
 *
 * @tparam D  Denominator value
 *
 * Provides compile time ratios, including reduced fractions
 */
template<size_t N, size_t D>
class ratio{
public:
  typedef size_t value_type;
  static constexpr value_type numerator = sign( N ) * sign( D ) * myAbs( N ) / gcd( N, D );
  static constexpr value_type denominator = myAbs( D ) / gcd( N, D );
  static constexpr double value = double( double( numerator ) / double( denominator ) );
  using type = ratio<numerator, denominator>;
  using invert_type = ratio<denominator, numerator>;

  /*! Value of ( numerator / denominator ) or of template parameters ( N / D )
   *
   * This allows the number to be easily used at runtime, converting the ratio
   * to a double value
   */
  constexpr operator double() const{
    return value;
  }

  /*! Value of 2 ratios multiplied together
   *
   * @tparam NUM  Numerator of parameter
   *
   * @tparam DEN  Denominator of parameter
   *
   * @param other  Ratio to multiply with
   *
   * @return Ratio of the result of ratio multiplication  
   *
   * Returns object of new ratio type, dependent on this object, and parameter
   */
  template<size_t NUM, size_t DEN>
  constexpr auto operator*( ratio<NUM, DEN> other ) const{
    typedef decltype( other ) OTHER;

    return ratio<numerator * OTHER::numerator, denominator * OTHER::denominator>();
  }

  /*! Value of 1 ratio divided by another
   *
   * @tparam NUM  Numerator of parameter
   *
   * @tparam DEN  Denominator of parameter
   *
   * @param other  Ratio to divide by
   *
   * @return Ratio of the result of ratio division
   *
   * Returns object of new ratio type, dependent on this object, and parameter
   */
  template<size_t NUM, size_t DEN>
  constexpr auto operator/( ratio<NUM, DEN> other ) const{
    typedef decltype( other ) OTHER;

    return ratio<numerator * OTHER::denominator, denominator * OTHER::numerator>();
  }

  /*!
   * @return
   */
  constexpr auto invert() const{
    return ratio<denominator, numerator>();
  }
};

/*! Value of ratio multiplied with a number
 *
 * @tparam T  Type of number being multiplied with ratio
 *
 * @tparam N  Numerator of ratio parameter
 *
 * @tparam D  Denominator of ratio parameter
 *
 * @param t  Number to multiply with
 *
 * @param r  Ratio to multiply with
 *
 * @return Number of type T, containing multiplication result
 */
template<typename T, size_t N, size_t D, typename std::enable_if<!std::is_same<T, ratio<N, D> >::value>::type>
constexpr T operator*( T t, ratio<N, D> r ){
  return t * double( r );
}

/*! Value of ratio multiplied with a number
 *
 * @tparam T  Type of number being multiplied with ratio
 *
 * @tparam N  Numerator of ratio parameter
 *
 * @tparam D  Denominator of ratio parameter
 *
 * @param r  Ratio to multiply with
 *
 * @param t  Number to multiply with
 *
 * @return Number of type T, containing multiplication result
 */
template<typename T, size_t N, size_t D, typename std::enable_if<!std::is_same<T, ratio<N, D> >::value>::type>
constexpr T operator*( ratio<N, D> r, T t ){
  return t * double( r );
}

/*! Value of number divided by ratio
 *
 * @tparam T  Type of number being divided
 *
 * @tparam N  Numerator of ratio parameter
 *
 * @tparam D  Denominator of ratio parameter
 *
 * @param t  Number being divided
 *
 * @param r  Ratio dividing by
 *
 * @return Number of type T, containing division result
 */
template<typename T, size_t N, size_t D, typename std::enable_if<!std::is_same<T, ratio<N, D> >::value>::type>
constexpr T operator/( T t, ratio<N, D> r ){
  using R = decltype( r );

  return ( t * R::denominator ) / R::numerator;
}

/*! Value of ratio divided by number
 *
 * @tparam T  Type of number being multiplied with ratio
 *
 * @tparam N  Numerator of ratio parameter
 *
 * @tparam D  Denominator of ratio parameter
 *
 * @param r  Ratio to divide
 *
 * @param t  Number to divide by
 *
 * @return Number of type T, containing division result
 */
template<typename T, size_t N, size_t D, typename std::enable_if<!std::is_same<T, ratio<N, D> >::value>::type >
constexpr T operator/( ratio<N, D> r, T t ){
  using R = decltype( r );

  return ( R::numerator / ( t * R::denominator ) );
}

/*! Check 'actual' equality of 2 ratios
 *
 * @tparam N1  Numerator of lhs
 *
 * @tparam D1  Denominator of lhs
 *
 * @tparam N2  Numerator of rhs
 *
 * @tparam D2  Denominator of rhs
 *
 * 'Actual' equality determined by value property
 */
template<size_t N1, size_t D1,
         size_t N2, size_t D2>
constexpr bool operator==( ratio<N1, D1> r1, ratio<N2, D2> r2 ){
  typedef decltype( r1 ) R1;
  typedef decltype( r2 ) R2;

  return R1::value == R2::value;
}

/*! Check 'actual' inequality of 2 ratios
 *
 * @tparam N1  Numerator of lhs
 *
 * @tparam D1  Denominator of lhs
 *
 * @tparam N2  Numerator of rhs
 *
 * @tparam D2  Denominator of rhs
 *
 * 'Actual' inequality determined by value property
 */
template<size_t N1, size_t D1,
         size_t N2, size_t D2>
constexpr bool operator!=( ratio<N1, D1> r1, ratio<N2, D2> r2 ){
  return !( r1 == r2 );
}

template<size_t N, size_t D>
constexpr double ratio<N, D>::value;
template<size_t N, size_t D>
constexpr typename ratio<N, D>::value_type ratio<N, D>::numerator;
template<size_t N, size_t D>
constexpr typename ratio<N, D>::value_type ratio<N, D>::denominator;

using unity = ratio<1,          1>;

using kilo  = ratio<1000,       1>;
using mega  = ratio<1000000,    1>;
using giga  = ratio<1000000000, 1>;
using milli = ratio<1,          1000>;
using micro = ratio<1,          1000000>;
using nano  = ratio<1,          1000000000>;
//using pico  = ratio<1,          1000000000000>;
//using femto = ratio<1,          1000000000000000>;

using kibi  = ratio<1024,          1>;
using mebi  = ratio<1048576,       1>;
using gibi  = ratio<1073741824,    1>;
//using tebi  = ratio<1099511627776, 1>;
}

#endif

