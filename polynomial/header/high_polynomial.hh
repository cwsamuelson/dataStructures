#include <map>
#include <set>

#include <named_point.hh>
#include <operators.hh>

namespace gsw{

class high_polynomial : public additive<high_polynomial>
                      , public multiplicative<high_polynomial>
                      , public multiplicative<high_polynomial, double>{
public:
  using input_point = vec<3, signed long long>;
  using value_type = double;
  using reference = value_type&;
  using const_reference = const value_type&;
  using storage_type = std::map<input_point, value_type>;

private:
  mutable storage_type mCoeff;

public:
  high_polynomial() = default;

  high_polynomial(std::initializer_list<input_point> il);

  template<typename inputIter>
  high_polynomial(inputIter first, inputIter last)
    : mCoeff(first, last){
  }

  template<typename U>
  high_polynomial(U&& eq){
  }

  std::set<value_type>
  solve(input_point hint = input_point::storage_t{1, 1}, unsigned int iterations = 6) const;

  template<typename U>
  high_polynomial&
  operator=( U&& eq){
  }

  high_polynomial&
  operator+=(const high_polynomial& hp);

  high_polynomial&
  operator-=(const high_polynomial& hp);

  high_polynomial&
  operator*=(const high_polynomial& hp);

  high_polynomial&
  operator*=(value_type d);

  high_polynomial&
  operator/=(const high_polynomial& hp);

  high_polynomial&
  operator/=(value_type d);

  high_polynomial&
  operator-() const;

  reference
  operator[](const input_point& point);

  const_reference
  operator[](const input_point& point) const;

  reference
  at(input_point point);

  const_reference
  at(input_point point) const;

  value_type
  operator()(input_point point) const;

  friend
  bool
  operator==(const high_polynomial& lhs, const high_polynomial& rhs);
};

bool
operator==(const high_polynomial& lhs, const high_polynomial& rhs);

}

