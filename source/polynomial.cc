#include<polynomial.hh>

using namespace std;
using namespace gsw;

set<double> polynomial::solve( double hint ){
  // should find (size - 1) roots
  std::set<double> roots;
  double root = hint;
  auto intermediate = *this;

  for( int i = 0; i < mCoeff.size(); ++i ){
    auto derivative = derive( intermediate );
    // Newton's method
    for( int i = 0; i < 6; ++i ){
      root =  root - ( intermediate( root ) / derivative( root ) );
    }

    roots.insert( root );

    vector<double> v;
    v.push_back( -root );
    v.push_back( 1 );

    intermediate /= polynomial( v.begin(), v.end() );
  }

  return roots;
}

unsigned int polynomial::order() const{
  reduce();

  if( mCoeff.size() > 0 ){
    return mCoeff.size() - 1;
  } else {
    return 0;
  }
}

polynomial& polynomial::operator+=( const polynomial& rhs ){
  unsigned int i;
  for( i = 0; i < std::min( mCoeff.size(), rhs.mCoeff.size() ); ++i ){
    mCoeff[i] += rhs.mCoeff[i];
  }

  while( rhs.mCoeff.size() > mCoeff.size() ){
    mCoeff.push_back( rhs.mCoeff[i++] );
  }

  return *this;
}

polynomial& polynomial::operator-=( const polynomial& rhs ){
  unsigned int i;
  for( i = 0; i < std::min( mCoeff.size(), rhs.mCoeff.size() ); ++i ){
    mCoeff[i] -= rhs.mCoeff[i];
  }

  while( rhs.mCoeff.size() > mCoeff.size() ){
    mCoeff.push_back( -rhs.mCoeff[i++] );
  }

  return *this;
}

polynomial& polynomial::operator*=( const polynomial& rhs ){
  storage_type vec( mCoeff.size() + rhs.mCoeff.size() - 1 );

  for( unsigned int i = 0; i < mCoeff.size(); ++i ){
    for( unsigned int j = 0; j < rhs.mCoeff.size(); ++j ){
      vec[i + j] += mCoeff[i] * rhs.mCoeff[j];
    }
  }

  // prevent incidental memory inflation
  /*! @todo consider whether this memory operation may be too much */
  vec.shrink_to_fit();

  mCoeff = move( vec );

  return *this;
}

polynomial& polynomial::operator*=( double d ){
  for( double& it : mCoeff ){
    it *= d;
  }

  return *this;
}

polynomial& polynomial::operator/=( const polynomial& rhs ){
  polynomial divisor = rhs;
  storage_type quotient( mCoeff.size() + divisor.mCoeff.size() - 1 );
  polynomial remainder = *this;

  // perform long division
  while( remainder.order() > 0 ){
    unsigned int term_order = remainder.order() - divisor.order();
    double term_value = ( quotient[term_order] = remainder.mCoeff.back() / divisor.mCoeff.back() );
    storage_type term_vec( term_order );
    term_vec.push_back( term_value );
    polynomial term( term_vec.begin(), term_vec.end() );
    remainder -= term * divisor;
  }

  // prevent incidental memory inflation
  /*! @todo consider whether this memory operation may be too much */
  quotient.shrink_to_fit();

  mCoeff = move( quotient );

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

bool gsw::operator==( const polynomial& lhs, const polynomial& rhs ){
  lhs.reduce();
  rhs.reduce();
  return lhs.mCoeff == rhs.mCoeff;
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

