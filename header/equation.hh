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

class equation : public additive<equation>,
                        multiplicative<equation>,
                        multiplicative<equation, double>{
private:
  typedef std::vector<double> storage_type;
  storage_type mCoeff;

void mv( const equation& eq ){
  mCoeff = eq.mCoeff;
}
void mv( equation&& eq ){
  mCoeff = std::move( eq.mCoeff );
}

public:
  equation() = default;

  template<class inputIter>
  equation( inputIter first, inputIter last ):
    mCoeff( first, last ){
  }

  template<typename U>
  equation( U&& eq ){
    mv( std::forward<U>( eq ) );
  }

  template<typename U>
  equation& operator=( U&& eq ){
    mv( std::forward<U>( eq ) );

    return *this;
  }

  equation& operator+=( const equation& rhs );

  equation& operator-=( const equation& rhs );

  equation& operator*=( const equation& rhs );

  equation& operator*=( double d );

  equation& operator/=( const equation& rhs );

  equation& operator/=( double d );

  double operator()( double X );

  friend equation derive( const equation& eq, unsigned int order );
  friend equation antiderive( const equation& eq );
  friend double integrate( const equation& eq, double upperBound, double lowerBound );
};

}

#endif

