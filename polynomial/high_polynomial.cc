#include<cmath>

#include<high_polynomial.hh>

using namespace gsw;

high_polynomial::reference
high_polynomial::operator[](const input_point& point)
{
  return mCoeff[point];
}

high_polynomial::const_reference
high_polynomial::operator[](const input_point& point) const
{
  return mCoeff[point];
}

high_polynomial::reference
high_polynomial::at( input_point point )
{
  return mCoeff.at(point);
}

high_polynomial::const_reference
high_polynomial::at( input_point point ) const
{
  return mCoeff.at(point);
}

high_polynomial::value_type
high_polynomial::operator()( input_point point ) const{
  double total = 0.0;

  for( auto coeff_data : mCoeff ){
    auto X = pow( point.x(), coeff_data.first.x() );
    auto Y = pow( point.y(), coeff_data.first.y() );

    total += X * Y * coeff_data.second;
  }

  return total;
}

bool
gsw::operator==( const high_polynomial& lhs, const high_polynomial& rhs ){
  return lhs.mCoeff == rhs.mCoeff;
}

