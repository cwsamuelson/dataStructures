#include<cmath>
#include<utility>

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
    auto Z = pow( point.z(), coeff_data.first.z() );

    total += X * Y * Z * coeff_data.second;
  }

  return total;
}

std::set<double>
high_polynomial::solve( input_point hint, unsigned int iterations ) const{
  ( void )hint;
  ( void )iterations;
  return {};
}
