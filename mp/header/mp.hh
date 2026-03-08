#pragma once

#include <compare>
#include <concepts>
#include <cstdint>
#include <format>
#include <limits>
#include <variant>
#include <vector>

namespace flp::MP {

struct Integer {
  constexpr
  Integer() noexcept = default;
  constexpr
  Integer(const Integer&) noexcept = default;
  constexpr
  Integer(Integer&&) noexcept = default;
  constexpr
  Integer& operator=(const Integer&) noexcept = default;
  constexpr
  Integer& operator=(Integer&&) noexcept = default;
  constexpr
  ~Integer() noexcept = default;

  template<std::integral Integer_t>
  constexpr
  Integer(const Integer_t& num) noexcept
    : negative(num < 0) {
    chunks.emplace_back(negative ? -num : num);
  }

  template<std::integral Integer_t>
  constexpr
  Integer& operator=(const Integer_t& num) noexcept {
    negative = num < 0;
    chunks.clear();

    if (negative) {
      chunks.emplace_back(-num);
    } else {
      chunks.emplace_back(num);
    }

    return *this;
  }

  // template<std::integral UInt>
  // constexpr
  // operator Integer() const noexcept {
  // }

  friend
  constexpr
  Integer operator+(const Integer& integer) noexcept {
    return integer;
  }

  friend
  constexpr
  Integer operator-(Integer integer) noexcept {
    integer.negative = not integer.negative;
    return integer;
  }

  friend
  constexpr
  Integer operator+(const Integer& lhs, const Integer& rhs) noexcept {
    return {};
  }

  friend
  constexpr
  Integer operator-(const Integer& lhs, const Integer& rhs) noexcept {
    return lhs + (-rhs);
  }

  friend
  constexpr
  Integer operator*(const Integer& lhs, const Integer& rhs) noexcept {
    return {};
  }

  friend
  constexpr
  Integer operator/(const Integer& lhs, const Integer& rhs) noexcept {
    return {};
  }

  friend
  constexpr
  Integer operator%(const Integer& lhs, const Integer& rhs) noexcept {
    return {};
  }

  template<std::integral Integer_t>
  friend
  constexpr
  Integer operator+(const Integer& integer, const Integer_t& integral) noexcept {
    return integer + Integer{integral};
  }

  template<std::integral Integer_t>
  friend
  constexpr
  Integer operator-(const Integer& integer, const Integer_t& integral) noexcept {
    return integer - Integer{integral};
  }

  template<std::integral Integer_t>
  friend
  constexpr
  Integer operator*(const Integer& integer, const Integer_t& integral) noexcept {
    return integer.sign<Integer_t>() * (integer.chunks * integral);
  }

  template<std::integral Integer_t>
  friend
  constexpr
  Integer operator/(const Integer& integer, const Integer_t& integral) noexcept {
    return integer.sign<Integer_t>() * (integer.chunks / integral);
  }

  template<std::integral Integer_t>
  friend
  constexpr
  Integer operator%(const Integer& integer, const Integer_t& integral) noexcept {
    return {};
  }

  template<std::integral Integer_t>
  friend
  constexpr
  Integer operator+(const Integer_t& integral, const Integer& integer) noexcept {
    return Integer{integral} + integer;
  }

  template<std::integral Integer_t>
  friend
  constexpr
  Integer operator-(const Integer_t& integral, const Integer& integer) noexcept {
    return Integer{integral} - integer;
  }

  template<std::integral Integer_t>
  friend
  constexpr
  Integer operator*(const Integer_t& integral, const Integer& integer) noexcept {
    return integer * integral;
  }

  template<std::integral Integer_t>
  friend
  constexpr
  Integer operator/(const Integer_t& integral, const Integer& integer) noexcept {
    return integer.sign<Integer_t>() * (integral / integer.chunks);
  }

  template<std::integral Integer_t>
  friend
  constexpr
  Integer operator%(const Integer_t& integral, const Integer& integer) noexcept {
    return {};
  }

  friend
  constexpr
  std::strong_ordering operator<=>(const Integer& lhs, const Integer& rhs) noexcept {
    if (lhs.negative and not rhs.negative) {
      return std::strong_ordering::less;
    }

    if (not lhs.negative and rhs.negative) {
      return std::strong_ordering::greater;
    }

    // same sign
    if (lhs.negative) {
      return rhs.chunks <=> lhs.chunks;
    } else {
      return lhs.chunks <=> rhs.chunks;
    }
  }

  template<std::unsigned_integral UInt>
  friend
  constexpr
  std::strong_ordering operator<=>(const Integer& integer, const UInt& uint) noexcept {
    if (integer.negative) {
      return std::strong_ordering::less;
    } else {
      return integer.chunks <=> uint;
    }
  }

  template<std::signed_integral SInt>
  friend
  constexpr
  std::strong_ordering operator<=>(const Integer& integer, const SInt& sint) noexcept {
    if (integer.negative) {
      if (sint < 0) {
        return sint <=> integer.chunks;
      } else {
        return std::strong_ordering::less;
      }
    } else {
      if (sint < 0) {
        return std::strong_ordering::greater;
      } else {
        return integer.chunks <=> sint;
      }
    }
  }

  friend
  constexpr
  bool operator==(const Integer&, const Integer&) noexcept = default;

  template<std::unsigned_integral UInt>
  friend
  constexpr
  bool operator==(const Integer& integer, const UInt& uint) noexcept {
    /*if (uint == 0) {
      return integer.chunks == 0;
    }

    if (integer.negative) {
      return false;
    }

    return integer.chunks == uint;*/
    return false;
  }

  template<std::signed_integral SInt>
  friend
  constexpr
  bool operator==(const Integer& integer, const SInt& sint) noexcept {
    /*if (sint == 0) {
      return integer.chunks == 0;
    }

    if (sint < 0) {
      return integer.negative and integer.chunks == -sint;
    }

    return not integer.negative and integer.chunks == sint;*/
    return false;
  }

  template<std::signed_integral Integral>
  [[nodiscard]]
  constexpr
  Integral sign() const {
    return negative ? -1 : 1;
  }

  void simplify() {
    while (not chunks.empty() and chunks.front() == 0) {
      chunks.pop_back();
    }

    chunks.shrink_to_fit();
  }

  bool negative = false;
  std::vector<uint64_t> chunks{};
};

[[nodiscard]]
constexpr
uint32_t overflow(const uint32_t lhs, const uint32_t rhs) noexcept {
  return static_cast<uint64_t>(std::numeric_limits<uint32_t>::max())
      - (static_cast<uint64_t>(lhs) + static_cast<uint64_t>(rhs));
}

[[nodiscard]]
constexpr
bool would_overflow(const uint32_t lhs, const uint32_t rhs) noexcept {
  return overflow(lhs, rhs) > 0;
}

struct SumState {
  uint64_t sum{};
  uint32_t overflow{};
};

[[nodiscard]]
constexpr
SumState add(const uint32_t lhs, const uint32_t rhs) noexcept {
  return {};
}

template<typename OStream>
OStream& operator<<(OStream& ostream, const Integer& integer) {
  if (integer.negative) {
    ostream << '-';
  }

  ostream << integer.chunks;

  return ostream;
}

} // namespace flp

template<>
struct std::formatter<flp::MP::Integer> : std::formatter<std::vector<uint64_t>> {
  auto format(const flp::MP::Integer& integer, std::format_context& context) const {
    if (integer.negative) {
      std::format_to(context.out(), "{} ", integer.negative);
    }

    return std::formatter<std::vector<uint64_t>>::format(integer.chunks, context);
  }
};
