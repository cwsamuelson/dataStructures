#include<polynomial.hh>

using namespace std;
using namespace gsw;

polynomial& polynomial::operator+=( const polynomial& rhs ){
  unsigned int i;
  for( i = 0; i < std::min( mCoeff.size(), rhs.mCoeff.size() ); ++i ){
    mCoeff[i] += rhs.mCoeff[i];
  }

  while( rhs.mCoeff.size() > mCoeff.size() ){
    mCoeff.push_back( rhs.mCoeff[i++] );
  }

  return ( *this );
}

polynomial& polynomial::operator-=( const polynomial& rhs ){
  unsigned int i;
  for( i = 0; i < std::min( mCoeff.size(), rhs.mCoeff.size() ); ++i ){
    mCoeff[i] -= rhs.mCoeff[i];
  }

  while( rhs.mCoeff.size() > mCoeff.size() ){
    mCoeff.push_back( -rhs.mCoeff[i++] );
  }

  return ( *this );
}

polynomial& polynomial::operator*=( const polynomial& rhs ){
  storage_type vec( mCoeff.size() + rhs.mCoeff.size() - 1 );

  for( unsigned int i = 0; i < mCoeff.size(); ++i ){
    for( unsigned int j = 0; j < rhs.mCoeff.size(); ++j ){
      vec[i + j] += mCoeff[i] * rhs.mCoeff[i];
    }
  }

  mCoeff = move( vec );

  return *this;
}

polynomial& polynomial::operator*=( double d ){
  for( double& it : mCoeff ){
    it *= d;
  }

  return ( *this );
}

polynomial& polynomial::operator/=( const polynomial& rhs ){
  storage_type vec( mCoeff.size() + rhs.mCoeff.size() - 1 );

  for( unsigned int i = 0; i < mCoeff.size(); ++i ){
    for( unsigned int j = 0; j < rhs.mCoeff.size(); ++j ){
      vec[i - j] -= mCoeff[i] / rhs.mCoeff[i];
    }
  }

  mCoeff = move( vec );

  return *this;
}

polynomial& polynomial::operator/=( double d ){
  for( double& it : mCoeff ){
    it /= d;
  }

  return *this;
}

double& polynomial::operator[]( size_t idx ){
  return mCoeff[idx];
}

double polynomial::operator()( double X ) const{
  double val = 0.0;

  for( unsigned int i = 0; i < mCoeff.size(); ++i ){
    val += std::pow( X, i ) * mCoeff[i];
  }

  return val;
}

bool gsw::operator==( const polynomial& eq, point p ){
  return eq( p.x ) == p.y;
}

bool gsw::operator<( const polynomial& eq, point p ){
  return eq( p.x ) < p.y;
}

bool gsw::operator>( const polynomial& eq, point p ){
  return eq( p.x ) > p.y;
}

bool gsw::operator<=( const polynomial& eq, point p ){
  return !( eq > p );
}

bool gsw::operator>=( const polynomial& eq, point p ){
  return !( eq < p );
}

bool gsw::operator==( point p, const polynomial& eq ){
  return eq == p;
}

bool gsw::operator<( point p, const polynomial& eq ){
  return p.y < eq( p.x );
}

bool gsw::operator>( point p, const polynomial& eq ){
  return p.y > eq( p.x );
}

bool gsw::operator<=( point p, const polynomial& eq ){
  return !( p > eq );
}

bool gsw::operator>=( point p, const polynomial& eq ){
  return !( p < eq );
}

polynomial gsw::derive( const polynomial& eq, unsigned int order ){
  if( order == 0 ){
    return eq;
  }

  polynomial ret;

  for( unsigned int i = 1; i < eq.mCoeff.size(); ++i ){
    ret.mCoeff.push_back( eq.mCoeff[i] * i );
  }

  return ret;
}

polynomial gsw::antiderive( const polynomial& eq ){
  polynomial ret;
  ret.mCoeff.push_back( 0 );

  for( unsigned int i = 0; i < eq.mCoeff.size(); ++i ){
    ret.mCoeff.push_back( eq.mCoeff[i] / ( i + 1 ) );
  }

  return ret;
}

double gsw::integrate( const polynomial& eq, double upperBound, double lowerBound ){
  polynomial anti( antiderive( eq ) );

  return anti( upperBound ) - anti( lowerBound );
}

