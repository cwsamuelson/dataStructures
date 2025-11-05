#pragma once

#include <compare>
#include <concepts>
#include <cstdint>
#include <format>
#include <limits>
#include <variant>

namespace flp {

struct Number {
  constexpr
  Number() noexcept = default;
  constexpr
  Number(const Number&) noexcept = default;
  constexpr
  Number(Number&&) noexcept = default;
  constexpr
  Number& operator=(const Number&) noexcept = default;
  constexpr
  Number& operator=(Number&&) noexcept = default;
  constexpr
  ~Number() noexcept = default;

  template<std::integral Integer>
  constexpr
  Number(const Integer& num) noexcept
    : negative(num < 0)
    , value(negative ? -num : num)
  {}

  template<std::integral Integer>
  constexpr
  Number& operator=(const Integer& num) noexcept {
    negative = num < 0;

    if (negative) {
      value = -num;
    } else {
      value = num;
    }

    return *this;
  }

  // template<std::integral UInt>
  // constexpr
  // operator Integer() const noexcept {
  // }

  friend
  constexpr
  Number operator+(const Number& number) noexcept {
    return number;
  }

  friend
  constexpr
  Number operator-(Number number) noexcept {
    number.negative = not number.negative;
    return number;
  }

  friend
  constexpr
  Number operator+(const Number& lhs, const Number& rhs) noexcept {
    Number result;

    if (lhs.value >= rhs.value) {
      if (lhs.negative != rhs.negative) {
        result.value = lhs.value - rhs.value;
      } else {
        result.value = lhs.value + rhs.value;
      }

      result.negative = lhs.negative;
    } else {
      result = rhs + lhs;
    }

    return result;
  }

  friend
  constexpr
  Number operator-(const Number& lhs, const Number& rhs) noexcept {
    return lhs + (-rhs);
  }

  friend
  constexpr
  Number operator*(const Number& lhs, const Number& rhs) noexcept {
    Number result;

    result.negative = lhs.negative != rhs.negative;
    result.value = lhs.value * rhs.value;

    return result;
  }

  friend
  constexpr
  Number operator/(const Number& lhs, const Number& rhs) noexcept {
    Number result;

    result.negative = lhs.negative != rhs.negative;
    result.value = lhs.value / rhs.value;

    return result;
  }

  friend
  constexpr
  Number operator%(const Number& lhs, const Number& rhs) noexcept {
    return {};
  }

  template<std::integral Integer>
  friend
  constexpr
  Number operator+(const Number& number, const Integer& integer) noexcept {
    return number + Number{integer};
  }

  template<std::integral Integer>
  friend
  constexpr
  Number operator-(const Number& number, const Integer& integer) noexcept {
    return number - Number{integer};
  }

  template<std::integral Integer>
  friend
  constexpr
  Number operator*(const Number& number, const Integer& integer) noexcept {
    return number.sign<Integer>() * (number.value * integer);
  }

  template<std::integral Integer>
  friend
  constexpr
  Number operator/(const Number& number, const Integer& integer) noexcept {
    return number.sign<Integer>() * (number.value / integer);
  }

  template<std::integral Integer>
  friend
  constexpr
  Number operator%(const Number& number, const Integer& integer) noexcept {
    return {};
  }

  template<std::integral Integer>
  friend
  constexpr
  Number operator+(const Integer& integer, const Number& number) noexcept {
    return Number{integer} + number;
  }

  template<std::integral Integer>
  friend
  constexpr
  Number operator-(const Integer& integer, const Number& number) noexcept {
    return Number{integer} - number;
  }

  template<std::integral Integer>
  friend
  constexpr
  Number operator*(const Integer& integer, const Number& number) noexcept {
    return number * integer;
  }

  template<std::integral Integer>
  friend
  constexpr
  Number operator/(const Integer& integer, const Number& number) noexcept {
    return number.sign<Integer>() * (integer / number.value);
  }

  template<std::integral Integer>
  friend
  constexpr
  Number operator%(const Integer& integer, const Number& number) noexcept {
    return {};
  }

  friend
  constexpr
  std::strong_ordering operator<=>(const Number& lhs, const Number& rhs) noexcept {
    if (lhs.negative and not rhs.negative) {
      return std::strong_ordering::less;
    }

    if (not lhs.negative and rhs.negative) {
      return std::strong_ordering::greater;
    }

    // same sign
    if (lhs.negative) {
      return rhs.value <=> lhs.value;
    } else {
      return lhs.value <=> rhs.value;
    }
  }

  template<std::unsigned_integral UInt>
  friend
  constexpr
  std::strong_ordering operator<=>(const Number& number, const UInt& uint) noexcept {
    if (number.negative) {
      return std::strong_ordering::less;
    } else {
      return number.value <=> uint;
    }
  }

  template<std::signed_integral SInt>
  friend
  constexpr
  std::strong_ordering operator<=>(const Number& number, const SInt& sint) noexcept {
    if (number.negative) {
      if (sint < 0) {
        return sint <=> number.value;
      } else {
        return std::strong_ordering::less;
      }
    } else {
      if (sint < 0) {
        return std::strong_ordering::greater;
      } else {
        return number.value <=> sint;
      }
    }
  }

  friend
  constexpr
  bool operator==(const Number&, const Number&) noexcept = default;

  template<std::unsigned_integral UInt>
  friend
  constexpr
  bool operator==(const Number& number, const UInt& uint) noexcept {
    if (uint == 0) {
      return number.value == 0;
    }

    if (number.negative) {
      return false;
    }

    return number.value == uint;
  }

  template<std::signed_integral SInt>
  friend
  constexpr
  bool operator==(const Number& number, const SInt& sint) noexcept {
    if (sint == 0) {
      return number.value == 0;
    }

    if (sint < 0) {
      return number.negative and number.value == -sint;
    }

    return not number.negative and number.value == sint;
  }

  template<std::signed_integral Integral>
  [[nodiscard]]
  constexpr
  Integral sign() const {
    return negative ? -1 : 1;
  }

  bool negative = false;
  uint64_t value{};
};

[[nodiscard]]
constexpr
bool would_overflow(const uint64_t lhs, const uint64_t rhs) noexcept {
  const auto growth_room = std::numeric_limits<uint64_t>::max() - lhs;
  return growth_room < rhs;
}

template<typename OStream>
OStream& operator<<(OStream& ostream, const Number& number) {
  if (number.negative) {
    ostream << '-';
  }

  ostream << number.value;

  return ostream;
}

} // namespace flp

template<>
struct std::formatter<flp::Number> : std::formatter<uint64_t> {
  constexpr auto format(const flp::Number& number, std::format_context& context) const {
    if (number.negative) {
      std::format_to(context.out(), "{} ", number.negative);
    }

    return std::formatter<uint64_t>::format(number.value, context);
  }
};
