#pragma once

#include <compare>
#include <concepts>
#include <cstdint>
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

  template<std::integral Integer>
  friend
  constexpr
  Number operator+(const Number& number, const Integer& integer) noexcept {
    return {};
  }

  template<std::integral Integer>
  friend
  constexpr
  Number operator-(const Number& number, const Integer& integer) noexcept {
    return {};
  }

  template<std::integral Integer>
  friend
  constexpr
  Number operator*(const Number& number, const Integer& integer) noexcept {
    return {};
  }

  template<std::integral Integer>
  friend
  constexpr
  Number operator/(const Number& number, const Integer& integer) noexcept {
    return {};
  }

  template<std::integral Integer>
  friend
  constexpr
  Number operator+(const Integer& integer, const Number& number) noexcept {
    return {};
  }

  template<std::integral Integer>
  friend
  constexpr
  Number operator-(const Integer& integer, const Number& number) noexcept {
    return {};
  }

  template<std::integral Integer>
  friend
  constexpr
  Number operator*(const Integer& integer, const Number& number) noexcept {
    return {};
  }

  template<std::integral Integer>
  friend
  constexpr
  Number operator/(const Integer& integer, const Number& number) noexcept {
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
    if (number.negative) {
      return false;
    }

    return number.value == uint;
  }

  template<std::signed_integral SInt>
  friend
  constexpr
  bool operator==(const Number& number, const SInt& sint) noexcept {
    return number.value == sint;
  }

  bool negative = false;
  uint64_t value{};
};

} // namespace flp
