#include<cmath>
#include<utility>

#include<high_polynomial.hh>

using namespace gsw;

bool
gsw::operator==( const high_polynomial& lhs, const high_polynomial& rhs ){
  return lhs.mCoeff == rhs.mCoeff;
}

high_polynomial&
high_polynomial::operator+=( const high_polynomial& rhs ){
  high_polynomial hp( *this );

  for( const auto& it : rhs.mCoeff ){
    hp.mCoeff[it.first] += it.second;
  }

  *this = std::move( hp );

  return *this;
}

high_polynomial&
high_polynomial::operator-=( const high_polynomial& rhs ){
  high_polynomial hp( *this );

  for( const auto& it : rhs.mCoeff ){
    hp.mCoeff[it.first] -= it.second;
  }

  *this = std::move( hp );

  return *this;
}

high_polynomial&
high_polynomial::operator*=( const high_polynomial& ){
  return *this;
}

high_polynomial&
high_polynomial::operator*=( double d ){
  for( auto& it : mCoeff ){
    it.second *= d;
  }

  return *this;
}

high_polynomial&
high_polynomial::operator/=( const high_polynomial& ){
  return *this;
}

high_polynomial&
high_polynomial::operator/=( double ){
  for( auto& it : mCoeff ){
    it.second /= d;
  }

  return *this;
}

high_polynomial
high_polynomial::operator-() const{
  high_polynomial hp( *this );

  for( auto& d : hp.mCoeff ){
    d.second = -d.second;
  }

  return *this;
}

double&
high_polynomial::operator[]( const input_point& point ){
  return mCoeff[point];
}

const double&
high_polynomial::operator[]( const input_point& point ) const{
  return mCoeff.at( point );
}

double
high_polynomial::operator()( const input_point& point ) const{
  double total = 0.0;

  for( auto coeff_data : mCoeff ){
    auto X = pow( point.x(), coeff_data.first.x() );
    auto Y = pow( point.y(), coeff_data.first.y() );
    auto Z = pow( point.z(), coeff_data.first.z() );

    total += X * Y * Z * coeff_data.second;
  }

  return total;
}
