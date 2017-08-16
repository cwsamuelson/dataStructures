#ifndef __EQUATION_HH__
#define __EQUATION_HH__

/*!
 * @example test-equation.cc
 */

#include<vector>
#include<functional>
#include<cmath>

#include<operators.hh>

namespace gsw{

class equation;

equation derive( const equation& eq, unsigned int order = 1 );
equation antiderive( const equation& eq );
double integrate( const equation& eq, double upperBound, double lowerBound );

/*! Equation wrapper.  Stores coefficients, and calculates a result
 *
 * @todo This class is a good candidate to implement constexpr-ness
 */
class equation : public additive<equation>,
                        multiplicative<equation>,
                        multiplicative<equation, double>{
private:
  using storage_type = std::vector<double>;
  storage_type mCoeff;

  void mv( const equation& eq ){
    mCoeff = eq.mCoeff;
  }

  void mv( equation&& eq ){
    mCoeff = std::move( eq.mCoeff );
  }

public:
  /*! default ctor
   */
  equation() = default;

  /*! Container ctor
   *
   * @tparam inputIter Iterator type used for coefficient input
   *
   * @param first iterator pointing to first coefficient
   *
   * @param last iterator pointing past the final coefficient
   *
   * Provide the coefficients for this equation from an extant container
   */
  template<class inputIter>
  equation( inputIter first, inputIter last ):
    mCoeff( first, last ){
  }

  /*! copy/move ctor
   *
   * @tparam U
   *
   * @param eq equation to copy/move from
   *
   * This ctor enables copy and move construction. eq is forwarded appropriately
   * for either copy or move
   */
  template<typename U>
  equation( U&& eq ){
    mv( std::forward<U>( eq ) );
  }

  /*! copy/move assignment
   *
   * @tparam U
   *
   * @param eq equation to copy/move from
   *
   * This enables copy and move operations. eq is forwarded appropriately for 
   * either copy or move
   */
  template<typename U>
  equation& operator=( U&& eq ){
    mv( std::forward<U>( eq ) );

    return *this;
  }

  /*! Add-assign operator
   *
   * @param rhs equation to be added to this one
   *
   * Adds the coefficients from this equation to those of rhs
   */
  equation& operator+=( const equation& rhs );

  /*! Subtract-assign operator
   *
   * @param rhs equation to be subtracted from this one
   *
   * Subtracts the coefficients from rhs from those of this equation
   */
  equation& operator-=( const equation& rhs );

  /*! Multiply-assign operator
   *
   * @param rhs equation to multiply with this one
   *
   * Multiplies rhs with this equation
   */
  equation& operator*=( const equation& rhs );

  /*! Multiply-assign operator
   *
   * @param d value to multiply each coefficient by
   *
   * Multiplies each coefficient in this equation by d
   */
  equation& operator*=( double d );

  /*! Divide-assign operator
   *
   * @param rhs equation to divide this equation by
   *
   * Divides this equation by rhs
   */
  equation& operator/=( const equation& rhs );

  /*! Divide-assign operator
   *
   * @param d value to divide each coefficient by
   *
   * Divides each coefficient in this equation by d
   */
  equation& operator/=( double d );

  /*! Find the value of the equation at a particular value
   *
   * @param X the x-value of the equation to 'solve' for
   *
   * Calculate a y-value for the given x-value
   */
  double operator()( double X );

  friend equation derive( const equation& eq, unsigned int order );
  friend equation antiderive( const equation& eq );
  friend double integrate( const equation& eq, double upperBound, double lowerBound );
};

}

#endif

