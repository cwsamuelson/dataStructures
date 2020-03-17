#include<cmath>
#include<utility>

#include<high_polynomial.hh>

using namespace gsw;

high_polynomial::high_polynomial(std::initializer_list<storage_type::value_type> il)
        : mCoeff(il) {
}

high_polynomial& high_polynomial::operator+=(const high_polynomial& hp) {
  for(const auto&[key, value] : hp.mCoeff) {
    mCoeff[key] += value;
  }

  return *this;
}

high_polynomial& high_polynomial::operator-=(const high_polynomial& hp) {
  for(const auto&[key, value] : hp.mCoeff) {
    mCoeff[key] -= value;
  }

  return *this;
}

high_polynomial& high_polynomial::operator*=(const high_polynomial& hp) {
  return *this;
}

high_polynomial& high_polynomial::operator*=(value_type d) {
  return *this;
}

high_polynomial& high_polynomial::operator/=(const high_polynomial& hp) {
  return *this;
}

high_polynomial& high_polynomial::operator/=(value_type d) {
  return *this;
}

high_polynomial high_polynomial::operator-() const {
  high_polynomial hp(*this);

  for(auto&[key, coeff] : hp.mCoeff) {
    coeff = -coeff;
  }

  return hp;
}

high_polynomial::reference high_polynomial::operator[](const input_point& point) {
  return mCoeff[point];
}

high_polynomial::const_reference high_polynomial::operator[](const input_point& point) const {
  return mCoeff[point];
}

high_polynomial::reference high_polynomial::at(const input_point& point) {
  return mCoeff.at(point);
}

high_polynomial::const_reference high_polynomial::at(const input_point& point) const {
  return mCoeff.at(point);
}

high_polynomial::value_type high_polynomial::operator()(input_point point) const {
  double total = 0.0;

  for(const auto& coeff_data : mCoeff) {
    auto X = pow(point.x(), coeff_data.first.x());
    auto Y = pow(point.y(), coeff_data.first.y());
    auto Z = pow(point.z(), coeff_data.first.z());

    total += X * Y * Z * coeff_data.second;
  }

  return total;
}

std::set<double> high_polynomial::solve(input_point hint, unsigned int iterations) const {
  (void) hint;
  (void) iterations;
  return {};
}

bool gsw::operator==(const high_polynomial& lhs, const high_polynomial& rhs) {
  return lhs.mCoeff == rhs.mCoeff;
}
