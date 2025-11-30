#pragma once

#include <compare>
#include <format>

namespace flp {

template<typename Type>
struct Complex {
  constexpr
  auto operator++();
  constexpr
  auto operator++(int);
  constexpr
  auto operator--();
  constexpr
  auto operator--(int);

  constexpr
  auto operator+(Complex);
  constexpr
  auto operator-(Complex);
  constexpr
  auto operator*(Complex);
  constexpr
  auto operator/(Complex);
  constexpr
  auto operator%(Complex);// ?

  constexpr
  auto operator+(Type);
  constexpr
  auto operator-(Type);
  constexpr
  auto operator*(Type);
  constexpr
  auto operator/(Type);
  constexpr
  auto operator%(Type);// ?

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
    return std::format_to(context.out(), "{} + {}i", number.real, number.imaginary);
  }
};
