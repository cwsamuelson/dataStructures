#include<equation.hh>

using namespace std;
using namespace gsw;

equation& equation::operator+=( const equation& rhs ){
  unsigned int i;
  for( i = 0; i < std::min( mCoeff.size(), rhs.mCoeff.size() ); ++i ){
    mCoeff[i] += rhs.mCoeff[i];
  }

  while( rhs.mCoeff.size() > mCoeff.size() ){
    mCoeff.push_back( rhs.mCoeff[i++] );
  }

  return ( *this );
}

equation& equation::operator-=( const equation& rhs ){
  unsigned int i;
  for( i = 0; i < std::min( mCoeff.size(), rhs.mCoeff.size() ); ++i ){
    mCoeff[i] -= rhs.mCoeff[i];
  }

  while( rhs.mCoeff.size() > mCoeff.size() ){
    mCoeff.push_back( -rhs.mCoeff[i++] );
  }

  return ( *this );
}

equation& equation::operator*=( const equation& rhs ){
  storage_type vec( mCoeff.size() + rhs.mCoeff.size() - 1 );

  for( unsigned int i = 0; i < mCoeff.size(); ++i ){
    for( unsigned int j = 0; j < rhs.mCoeff.size(); ++j ){
      vec[i + j] += mCoeff[i] * rhs.mCoeff[i];
    }
  }

  mCoeff = move( vec );

  return *this;
}

equation& equation::operator*=( double d ){
  for( double& it : mCoeff ){
    it *= d;
  }

  return ( *this );
}

equation& equation::operator/=( const equation& rhs ){
  storage_type vec( mCoeff.size() + rhs.mCoeff.size() - 1 );

  for( unsigned int i = 0; i < mCoeff.size(); ++i ){
    for( unsigned int j = 0; j < rhs.mCoeff.size(); ++j ){
      vec[i - j] -= mCoeff[i] / rhs.mCoeff[i];
    }
  }

  mCoeff = move( vec );

  return *this;
}

equation& equation::operator/=( double d ){
  for( double& it : mCoeff ){
    it /= d;
  }

  return *this;
}

double equation::operator()( double X ){
  double val = 0.0;

  for( unsigned int i = 0; i < mCoeff.size(); ++i ){
    val += std::pow( X, i ) * mCoeff[i];
  }

  return val;
}

equation gsw::derive( const equation& eq, unsigned int order ){
  if( order == 0 ){
    return eq;
  }

  equation ret;

  for( unsigned int i = 1; i < eq.mCoeff.size(); ++i ){
    ret.mCoeff.push_back( eq.mCoeff[i] * i );
  }

  return ret;
}

equation gsw::antiderive( const equation& eq ){
  equation ret;
  ret.mCoeff.push_back( 0 );

  for( unsigned int i = 0; i < eq.mCoeff.size(); ++i ){
    ret.mCoeff.push_back( eq.mCoeff[i] / ( i + 1 ) );
  }

  return ret;
}

double gsw::integrate( const equation& eq, double upperBound, double lowerBound ){
  equation anti( antiderive( eq ) );

  return anti( upperBound ) - anti( lowerBound );
}

