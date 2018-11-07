#ifndef __HIGH_POLY_HH__
#define __HIGH_POLY_HH__

#include<utility>
#include<map>
#include<set>

#include<named_point.hh>

namespace gsw{

using input_point = point3;

/*! Polynomial class that supports up to 3D input, and calculates output
 *
 */
class high_polynomial{
private:
  using storage_type = std::map<input_point, double>;

  storage_type mCoeff;

public:
  high_polynomial() = default;

  high_polynomial( std::initializer_list<input_point> il );

  template<typename inputIter>
  high_polynomial( inputIter first, inputIter last )
    : mCoeff( first, last ){
  }

  high_polynomial( const high_polynomial& other )
    : mCoeff( other.mCoeff ){
  }

  high_polynomial( high_polynomial&& other )
    : mCoeff( std::move( other.mCoeff ) ){
  }

  std::set<double>
  solve( input_point hint, unsigned int iterations = 6 ) const;

  high_polynomial&
  operator=( const high_polynomial& other ){
    mCoeff = other.mCoeff;

    return *this;
  }

  high_polynomial&
  operator=( high_polynomial&& eq ){
    mCoeff = std::move( eq.mCoeff );

    return *this;
  }

  high_polynomial&
  operator+=( const high_polynomial& hp );

  high_polynomial&
  operator-=( const high_polynomial& hp );

  high_polynomial&
  operator*=( const high_polynomial& hp );

  high_polynomial&
  operator*=( double d );

  high_polynomial&
  operator/=( const high_polynomial& hp );

  high_polynomial&
  operator/=( double d );

  high_polynomial
  operator-() const;

  double&
  operator[]( const input_point& point );

  const double&
  operator[]( const input_point& point ) const;

  double
  operator()( const input_point& point ) const;

  friend
  bool
  operator==( const high_polynomial& lhs, const high_polynomial& rhs );
};

bool
operator==( const high_polynomial& lhs, const high_polynomial& rhs );

}

#endif
