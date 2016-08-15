#ifndef __EQUATION_HH__
#define __EQUATION_HH__

#include<vector>
#include<functional>
#include<cmath>

class equation{
private:
  std::vector<double> mCoeff;

  template<class operation>
  std::vector<double> merge(const std::vector<double>& small, const std::vector<double>& large, bool swapOperands = false, operation op = operation()){
    std::vector<double> vec;
    int i = 0;

    vec = large;

    for(auto it:small){
      if(swapOperands){
        vec[i] = op(vec[i], it);
      } else {
        vec[i] = op(it, vec[i]);
      }
      ++i;
    }

    return vec;
  }

public:
  equation() = default;
  template<class inputIter>
  equation(inputIter first, inputIter last):
    mCoeff(first, last){
  }
  equation(const equation& eq):
    mCoeff(eq.mCoeff){
  }

  equation& operator=(const equation& eq){
    mCoeff = eq.mCoeff;

    return (*this);
  }

  equation operator+(const equation& rhs){
    equation eq(*this);

    eq += rhs;

    return eq;
  }
  equation& operator+=(const equation& rhs){
    if(mCoeff.size() > rhs.mCoeff.size()){
      mCoeff = merge<std::plus<double> >(rhs.mCoeff, mCoeff);
    } else {
      mCoeff = merge<std::plus<double> >(mCoeff, rhs.mCoeff);
    }

    return (*this);
  }
  equation operator-(const equation& rhs){
    equation eq(*this);

    eq -= rhs;

    return eq;
  }
  equation& operator-=(const equation& rhs){
    if(mCoeff.size() > rhs.mCoeff.size()){
      mCoeff = merge<std::minus<double> >(rhs.mCoeff, mCoeff, true);
    } else {
      mCoeff = merge<std::minus<double> >(mCoeff, rhs.mCoeff);
    }

    return (*this);
  }

  double operator()(const double X){
    double val = 0.0;

    for(unsigned int i = 0; i < mCoeff.size(); ++i){
      val += std::pow(X, i) * mCoeff[i];
    }

    return val;
  }
};

#endif

