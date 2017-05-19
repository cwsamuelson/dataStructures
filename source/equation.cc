#include<equation.hh>

using namespace std;

/*! Copy constructor
 *
 * @param eq  Equation to be copied from.
 */
equation::equation( const equation& eq ):
  mCoeff( eq.mCoeff ){
}

/*! Move constructor
 *
 * @param eq  Equation to be moved from.
 */
equation::equation( equation&& eq ):
  mCoeff( forward<storage_type>( eq.mCoeff ) ){
}

/*! Copy assignment operator
 *
 * @param eq  Equation to be copied from
 */
equation& equation::operator=( const equation& eq ){
  mCoeff = eq.mCoeff;

  return *this;
}

/*! Move assignment operator
 *
 * @param eq  Equation to be moved from
 */
equation& equation::operator=( equation&& eq ){
  mCoeff = forward<storage_type>( eq.mCoeff );

  return *this;
}

/*! Addition operator
 *
 * @param rhs  Right hand side of + operator
 *
 * @return Result of addition operation
 *
 * Add 2 equations together
 */
equation equation::operator+( const equation& rhs ){
  equation eq( *this );

  eq += rhs;

  return eq;
}

/*! Add-assignment operator
 *
 * @param rhs  Right hand side of the += operator
 *
 * @return Reference to lhs/the result of the addition operation
 *
 * Adds 2 equations together, assigns result to lhs
 */
equation& equation::operator+=( const equation& rhs ){
  if( mCoeff.size() > rhs.mCoeff.size() ){
    mCoeff = merge<std::plus<double> >( rhs.mCoeff, mCoeff );
  } else {
    mCoeff = merge<std::plus<double> >( mCoeff, rhs.mCoeff );
  }

  return ( *this );
}

/*! Subtraction operator
 *
 * @param rhs  Right hand side of - operator
 *
 * @return Result of subtraction operation
 *
 * Subtract rhs from lhs
 */
equation equation::operator-( const equation& rhs ){
  equation eq( *this );

  eq -= rhs;

  return eq;
}

/*! Subtract-assignment operator
 *
 * @param rhs Right hand side of the -= operator
 *
 * @return Reference to lhs/the result of the subtraction operation
 *
 * Subtracts 2 equations, assigns result to lhs
 */
equation& equation::operator-=( const equation& rhs ){
  if( mCoeff.size() > rhs.mCoeff.size() ){
    mCoeff = merge<std::minus<double> >( rhs.mCoeff, mCoeff, true );
  } else {
    mCoeff = merge<std::minus<double> >( mCoeff, rhs.mCoeff );
  }

  return ( *this );
}

equation equation::operator*( const equation& rhs ){
  storage_type vec( mCoeff.size() + rhs.mCoeff.size() - 1 );

  for( unsigned int i = 0; i < mCoeff.size(); ++i ){
    for( unsigned int j = 0; j < rhs.mCoeff.size(); ++j ){
      vec[i + j] += mCoeff[i] * rhs.mCoeff[i];
    }
  }

  return equation( vec.begin(), vec.end() );
}

equation& equation::operator*=( const equation& rhs ){
  ( *this ) = ( *this ) * rhs;
  return ( *this );
}

equation equation::operator*( double d ){
  equation eq( *this );

  eq *= d;

  return eq;
}

equation& equation::operator*=( double d ){
  for( double& it : mCoeff ){
    it *= d;
  }

  return ( *this );
}

equation equation::operator/( const equation& rhs ){
  storage_type vec( mCoeff.size() + rhs.mCoeff.size() - 1 );

  for( unsigned int i = 0; i < mCoeff.size(); ++i ){
    for( unsigned int j = 0; j < rhs.mCoeff.size(); ++j ){
      vec[i - j] -= mCoeff[i] / rhs.mCoeff[i];
    }
  }

  return equation( vec.begin(), vec.end() );
}

equation equation::operator/( double d ){
  equation eq( *this );

  eq /= d;

  return eq;
}

equation& equation::operator/=( double d ){
  for( double& it : mCoeff ){
    it /= d;
  }

  return ( *this );
}

double equation::operator()( const double X ){
  double val = 0.0;

  for( unsigned int i = 0; i < mCoeff.size(); ++i ){
    val += std::pow( X, i ) * mCoeff[i];
  }

  return val;
}

equation derive( const equation& eq, unsigned int order ){
  if( order == 0 ){
    return eq;
  }

  equation ret;

  for( unsigned int i = 1; i < eq.mCoeff.size(); ++i ){
    ret.mCoeff.push_back( eq.mCoeff[i] * i );
  }

  return ret;
}

equation antiderive( const equation& eq ){
  equation ret;
  ret.mCoeff.push_back( 0 );

  for( unsigned int i = 0; i <= eq.mCoeff.size(); ++i ){
    ret.mCoeff.push_back( eq.mCoeff[i] / ( i + 1 ) );
  }

  return ret;
}

double integrate( const equation& eq, double upperBound, double lowerBound ){
  equation anti( antiderive( eq ) );

  return anti( upperBound ) - anti( lowerBound );
}

