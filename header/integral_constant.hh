#ifndef __INTEGRAL_CONSTANT_HH__
#define __INTEGRAL_CONSTANT_HH__

namespace gsw{

template<class T, T v>
class integral_constant{
public:
  using value_type = T;
  using type = integral_constant;
  static const T value = v;

  constexpr operator value_type() const noexcept{
    return value;
  }

  constexpr T operator()() const noexcept{
    return value;
  }
};

template<bool B>
using bool_constant = integral_constant<bool, B>;

}

#endif

