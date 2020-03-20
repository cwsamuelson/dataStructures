#include <map>
#include <set>

#include <named_point.hh>
#include <operators.hh>

namespace gsw {

class high_polynomial
        : public additive<high_polynomial>
          , public multiplicative<high_polynomial>
          , public multiplicative<high_polynomial, double> {
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
  high_polynomial(std::initializer_list<storage_type::value_type> il);
  template<typename inputIter>
  high_polynomial(inputIter first, inputIter last)
          : mCoeff(first, last) {
  }
  high_polynomial(const high_polynomial& hp)
    : mCoeff(hp.mCoeff)
  {}
  high_polynomial(high_polynomial&& hp) noexcept
    : mCoeff(std::move(hp.mCoeff))
  {}

  std::set<value_type> solve(input_point hint = input_point::storage_t{ 1, 1 }, unsigned int iterations = 6) const;

  template<typename U>
  high_polynomial& operator=(U&& eq) {
    mCoeff = std::forward<storage_type>(eq.mCoeff);

    return *this;
  }

  high_polynomial& operator+=(const high_polynomial& hp);

  high_polynomial& operator-=(const high_polynomial& hp);

  high_polynomial& operator*=(const high_polynomial& hp);

  high_polynomial& operator*=(value_type d);

  high_polynomial& operator/=(const high_polynomial& hp);

  high_polynomial& operator/=(value_type d);

  high_polynomial operator-() const;

  [[nodiscard]]
  reference operator[](const input_point& point);

  [[nodiscard]]
  const_reference operator[](const input_point& point) const;

  [[nodiscard]]
  reference at(const input_point& point);

  [[nodiscard]]
  const_reference at(const input_point& point) const;

  [[nodiscard]]
  value_type operator()(input_point point) const;

  friend bool operator==(const high_polynomial& lhs, const high_polynomial& rhs);
};

[[nodiscard]]
bool operator==(const high_polynomial& lhs, const high_polynomial& rhs);

}

