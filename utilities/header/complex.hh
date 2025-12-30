#pragma once

#include <cmath>
#include <compare>
#include <format>

namespace flp {

template<typename Type>
struct Complex {
  // constexpr
  // auto operator++();
  // constexpr
  // auto operator++(int);
  // constexpr
  // auto operator--();
  // constexpr
  // auto operator--(int);

  constexpr
  Complex operator+() const noexcept {
    return {+real, +imaginary};
  }

  constexpr
  Complex operator-() const noexcept {
    return {-real, -imaginary};
  }

  constexpr
  Complex& operator+=(const Complex& other) noexcept {
    real += other.real;
    imaginary += other.imaginary;
    return *this;
  }

  constexpr
  Complex& operator-=(const Complex& other) noexcept {
    real -= other.real;
    imaginary -= other.imaginary;
    return *this;
  }

  constexpr
  Complex& operator*=(const Complex& other) noexcept {
    const Complex complex(*this);
    *this = complex * other;
    return *this;
  }

  constexpr
  Complex& operator/=(const Complex& other) noexcept {
    const Complex complex(*this);
    *this = complex / other;
    return *this;
  }

  // ?
  constexpr
  Complex& operator%=(const Complex& other) noexcept {
    return *this;
  }

  friend
  constexpr
  Complex operator+(const Complex& lhs, const Complex& rhs) noexcept {
    Complex value(lhs);
    value += rhs;
    return value;
  }

  friend
  constexpr
  Complex operator-(const Complex& lhs, const Complex& rhs) noexcept {
    Complex value(lhs);
    value -= rhs;
    return value;
  }

  friend
  constexpr
  Complex operator*(const Complex& lhs, const Complex& rhs) noexcept {
    return {
      lhs.real * rhs.real - lhs.imaginary * rhs.imaginary,
      lhs.real * rhs.imaginary + lhs.imaginary * rhs.real
    };
  }

  friend
  constexpr
  Complex operator/(const Complex& lhs, const Complex& rhs) noexcept {
    const Type denom = rhs.real * rhs.real + rhs.imaginary * rhs.imaginary;
    return {
      (lhs.real * rhs.real + lhs.imaginary * rhs.imaginary) / denom,
      (lhs.imaginary * rhs.real - lhs.real * rhs.imaginary) / denom
    };
  }

  // ?
  friend
  constexpr
  Complex operator%(const Complex& lhs, const Complex& rhs) noexcept {
    Complex value(lhs);
    value %= rhs;
    return value;
  }

  friend
  constexpr
  Complex operator+(const Complex& complex, const Type& value) noexcept {
    return complex + Complex{value, 0};
  }

  friend
  constexpr
  Complex operator-(const Complex& complex, const Type& value) noexcept {
    return complex - Complex{value, 0};
  }

  friend
  constexpr
  Complex operator*(const Complex& complex, const Type& value) noexcept {
    return complex * Complex{value, 0};
  }

  friend
  constexpr
  Complex operator/(const Complex& complex, const Type& value) noexcept {
    return { complex.real / value, complex.imaginary / value };
  }

  // ?
  friend
  constexpr
  Complex operator%(const Complex& complex, const Type& value) noexcept {
    return complex % Complex{value, 0};
  }

  friend
  constexpr
  Complex operator+(const Type& value, const Complex& complex) noexcept {
    return complex + value;
  }

  friend
  constexpr
  Complex operator-(const Type& value, const Complex& complex) noexcept {
    return -complex + value;
  }

  friend
  constexpr
  Complex operator*(const Type& value, const Complex& complex) noexcept {
    return complex * value;
  }

  friend
  constexpr
  Complex operator/(const Type& value, const Complex& complex) noexcept {
    // this is 100% wrong
    return complex / value;
  }

  // ?
  friend
  constexpr
  Complex operator%(const Type& value, const Complex& complex) noexcept {
    return complex % value;
  }

  constexpr
  Complex conjugate() const noexcept {
    return {real, -imaginary};
  }

  constexpr
  auto magnitude() const noexcept {
    if constexpr(std::integral<Type>) {
      return (float)std::sqrt((float)(real * real) + (float)(imaginary * imaginary));
    } else {
      return std::sqrt(real * real + imaginary * imaginary);
    }
  }

  constexpr
  Type r() const noexcept {
    return real;
  }

  constexpr
  Type i() const noexcept {
    return imaginary;
  }

  friend
  constexpr
  auto operator<=>(const Complex&, const Complex&) noexcept = default;

  friend
  constexpr
  auto operator<=>(const Complex&, const Type&) noexcept;

  Type real{};
  Type imaginary{};
};

}

template<typename Type>
struct std::formatter<flp::Complex<Type>> : std::formatter<uint64_t> {
  constexpr
  auto format(const flp::Complex<Type>& number, std::format_context& context) const {
    return std::format_to(context.out(), "{} {} i{}", number.real, number.imaginary < 0.f ? '-' : '+', std::abs(number.imaginary));
  }
};

template<typename OStream, typename Type>
OStream& operator<<(OStream& ostream, const flp::Complex<Type>& complex) noexcept {
  return ostream << std::format("{}", complex);
}
