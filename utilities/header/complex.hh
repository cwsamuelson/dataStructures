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
    return {real, imaginary};
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
    *this = complex * other;
    return *this;
  }

  // ?
  constexpr
  Complex& operator%=(const Complex& other) noexcept {
    return *this;
  }

  constexpr
  Complex operator+(const Complex& other) const noexcept {
    Complex value(*this);
    value += other;
    return value;
  }

  constexpr
  Complex operator-(const Complex& other) const noexcept {
    Complex value(*this);
    value -= other;
    return value;
  }

  constexpr
  Complex operator*(const Complex& other) const noexcept {
    return {
      real * other.real - imaginary * other.imaginary,
      real * other.imaginary + imaginary * other.real
    };
  }

  constexpr
  Complex operator/(const Complex& other) const noexcept {
    const Type denom = other.real * other.real + other.imaginary * other.imaginary;
    return {
      (real * other.real + imaginary * other.imaginary) / denom,
      (imaginary * other.real - real * other.imaginary) / denom
    };
  }

  // ?
  constexpr
  Complex operator%(const Complex& other) const noexcept {
    Complex value(*this);
    value %= other;
    return value;
  }

  constexpr
  Complex operator+(const Type& value) const noexcept {
    return (*this) + Complex{value, 0};
  }

  constexpr
  Complex operator-(const Type& value) const noexcept {
    return (*this) - Complex{value, 0};
  }

  constexpr
  Complex operator*(const Type& value) const noexcept {
    return (*this) * Complex{value, 0};
  }

  constexpr
  Complex operator/(const Type& value) const noexcept {
    return (*this) / Complex{value, 0};
  }

  // ?
  constexpr
  Complex operator%(const Type& value) const noexcept {
    return (*this) % Complex{value, 0};
  }

  constexpr
  friend
  Complex operator+(const Type& value, const Complex& complex) noexcept {
    return complex + value;
  }

  constexpr
  friend
  Complex operator-(const Type& value, const Complex& complex) noexcept {
    return complex - value;
  }

  constexpr
  friend
  Complex operator*(const Type& value, const Complex& complex) noexcept {
    return complex * value;
  }

  constexpr
  friend
  Complex operator/(const Type& value, const Complex& complex) noexcept {
    return complex / value;
  }

  // ?
  constexpr
  friend
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
