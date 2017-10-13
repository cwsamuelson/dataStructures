#ifndef __POLYNOMIAL_HH__
#define __POLYNOMIAL_HH__

/*!
 * @example test-polynomial.cc
 */

#include<set>
#include<vector>
#include<functional>
#include<cmath>

#include<operators.hh>

namespace gsw{

class polynomial;

struct point{
  double x;
  double y;
};

/*! Polynomial wrapper.  Stores coefficients, and calculates a result
 *
 * @todo This class is a good candidate to implement constexpr-ness
 */
class polynomial : public additive<polynomial>,
                          multiplicative<polynomial>,
                          multiplicative<polynomial, double>{
private:
  using storage_type = std::vector<double>;
  storage_type mCoeff;

  void mv( const polynomial& eq ){
    mCoeff = eq.mCoeff;
  }

  void mv( polynomial&& eq ){
    mCoeff = std::move( eq.mCoeff );
  }

public:
  /*! default ctor
   */
  polynomial() = default;

  /*! Container ctor
   *
   * @tparam inputIter Iterator type used for coefficient input
   *
   * @param first iterator pointing to first coefficient
   *
   * @param last iterator pointing past the final coefficient
   *
   * Provide the coefficients for this polynomial from an extant container
   */
  template<typename inputIter>
  polynomial( inputIter first, inputIter last ):
    mCoeff( first, last ){
  }

  /*! copy/move ctor
   *
   * @tparam U
   *
   * @param eq polynomial to copy/move from
   *
   * This ctor enables copy and move construction. eq is forwarded appropriately
   * for either copy or move
   */
  template<typename U>
  polynomial( U&& eq ){
    mv( std::forward<U>( eq ) );
  }

  /*!
   */
  std::set<double> solve( double hint = 1.0 );

  /*! copy/move assignment
   *
   * @tparam U
   *
   * @param eq polynomial to copy/move from
   *
   * @return Resulting polynomial after assignment
   *
   * This enables copy and move operations. eq is forwarded appropriately for 
   * either copy or move
   */
  template<typename U>
  polynomial& operator=( U&& eq ){
    mv( std::forward<U>( eq ) );

    return *this;
  }

  /*! Add-assign operator
   *
   * @param rhs polynomial to be added to this one
   *
   * @return Resulting polynomial after subtraction
   *
   * Adds the coefficients from this polynomial to those of rhs
   */
  polynomial& operator+=( const polynomial& rhs );

  /*! Subtract-assign operator
   *
   * @param rhs polynomial to be subtracted from this one
   *
   * @return Resulting polynomial after subtraction
   *
   * Subtracts the coefficients from rhs from those of this polynomial
   */
  polynomial& operator-=( const polynomial& rhs );

  /*! Multiply-assign operator
   *
   * @param rhs polynomial to multiply with this one
   *
   * @return Resulting polynomial after multiplication
   *
   * Multiplies rhs with this polynomial
   */
  polynomial& operator*=( const polynomial& rhs );

  /*! Multiply-assign operator
   *
   * @param d value to multiply each coefficient by
   *
   * @return Resulting polynomial after multiplication
   *
   * Multiplies each coefficient in this polynomial by d
   */
  polynomial& operator*=( double d );

  /*! Divide-assign operator
   *
   * @param rhs polynomial to divide this polynomial by
   *
   * @return Resulting polynomial after division
   *
   * Divides this polynomial by rhs
   */
  polynomial& operator/=( const polynomial& rhs );

  /*! Divide-assign operator
   *
   * @param d value to divide each coefficient by
   *
   * @return Resulting polynomial after division
   *
   * Divides each coefficient in this polynomial by d
   */
  polynomial& operator/=( double d );

  /*!
   *
   * @param idx
   *
   * @return
   */
  double& operator[]( size_t idx );

  /*! Find the value of the polynomial at a particular value
   *
   * @param X the x-value of the polynomial to compute
   *
   * @return Result of solving the polynomial for X
   *
   * Calculate a y-value for the given x-value
   */
  double operator()( double X ) const;

  /*!
   *
   * @param eq
   *
   * @param p
   *
   * @return
   */
  friend bool operator==( const polynomial& eq, point p );

  /*!
   *
   * @param eq
   *
   * @param p
   *
   * @return
   */
  friend bool operator<( const polynomial& eq, point p );

  /*!
   *
   * @param eq
   *
   * @param p
   *
   * @return
   */
  friend bool operator<=( const polynomial& eq, point p );

  /*!
   *
   * @param eq
   *
   * @param p
   *
   * @return
   */
  friend bool operator>( const polynomial& eq, point p );

  /*!
   *
   * @param eq
   *
   * @param p
   *
   * @return
   */
  friend bool operator>=( const polynomial& eq, point p );

  /*!
   *
   * @param eq
   *
   * @param p
   *
   * @return
   */
  friend bool operator==( point p, const polynomial& eq );

  /*!
   *
   * @param eq
   *
   * @param p
   *
   * @return
   */
  friend bool operator<( point p, const polynomial& eq );

  /*!
   *
   * @param eq
   *
   * @param p
   *
   * @return
   */
  friend bool operator<=( point p, const polynomial& eq );

  /*!
   *
   * @param eq
   *
   * @param p
   *
   * @return
   */
  friend bool operator>( point p, const polynomial& eq );

  /*!
   *
   * @param eq
   *
   * @param p
   *
   * @return
   */
  friend bool operator>=( point p, const polynomial& eq );

  /*!
   */
  friend polynomial derive( const polynomial& eq, unsigned int order );

  /*!
   */
  friend polynomial antiderive( const polynomial& eq );

  /*!
   */
  friend double integrate( const polynomial& eq, double upperBound, double lowerBound );
};

bool operator==( const polynomial& eq, point p );
bool operator<(  const polynomial& eq, point p );
bool operator<=( const polynomial& eq, point p );
bool operator>(  const polynomial& eq, point p );
bool operator>=( const polynomial& eq, point p );

bool operator==( point p, const polynomial& eq );
bool operator<(  point p, const polynomial& eq );
bool operator<=( point p, const polynomial& eq );
bool operator>(  point p, const polynomial& eq );
bool operator>=( point p, const polynomial& eq );

polynomial derive( const polynomial& eq, unsigned int order = 1 );
polynomial antiderive( const polynomial& eq );
double integrate( const polynomial& eq, double upperBound, double lowerBound );

}

#endif

