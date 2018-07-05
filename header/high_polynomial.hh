#include<map>

#include<named_point.hh>

namespace gsw{

using input_point = point3;

class high_polynomial{
private:
  using storage_type = std::map<input_point, double>;

  mutable storage_type mCoeff;

public:
  high_polynomial() = default;

  hipgh_polynomial( std::initializer_list<input_point> il );

  template<typename inputIter>
  high_polynomial( inputIter first, inputIter last )
    : mCoeff( first, last ){
  }

  template<typename U>
  high_polynomial( U&& eq ){
  }

  std::set<double>
  solve( input_point hint = {1, 1}, unsigned int iterations = 6 ) const;

  template<typename U>
  high_polynomial&
  operator=(  U&& eq ){
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

  high_polynomial&
  operator-() const;

  double&
  operator[]( input_point point );

  const double&
  operator[]( input_point point ) const;

  double
  operator()( input_point point ) const;

  friend
  bool
  operator==( const high_polynomial& lhs, const high_polynomial& rhs );
};

bool
operator==( const high_polynomial& lhs, const high_polynomial& rhs );

}

