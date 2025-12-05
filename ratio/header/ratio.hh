#pragma once

#include <algorithms/numerics.hh>

#include <concepts>
#include <cstdint>
#include <format>

namespace flp {

template<typename Type = int64_t>
struct Ratio {
  Type numerator{};
  Type denominator{};

  template<typename OType>
  [[nodiscard]]
  constexpr
  operator OType() const noexcept {
    return static_cast<OType>(numerator) / static_cast<OType>(denominator);
  }

  [[nodiscard]]
  constexpr
  Ratio invert() const noexcept {
    return { denominator, numerator };
  }

  [[nodiscard]]
  constexpr
  Type gcd() const noexcept {
    return flp::gcd(numerator, denominator);
  }

  [[nodiscard]]
  constexpr
  Type lcm() const noexcept {
    return flp::lcm(numerator, denominator);
  }

  friend
  constexpr
  auto operator<=>(const Ratio& lhs, const Ratio& rhs) noexcept {
    if (lhs.denominator == rhs.denominator) {
      return lhs.numerator <=> rhs.numerator;
    }

    const auto target = flp::lcm(lhs.denominator, rhs.denominator);
    const auto lmul = target / lhs.denominator;
    const auto rmul = target / rhs.denominator;

    return lhs.numerator * lmul <=> rhs.numerator * rmul;
  }

  friend
  constexpr
  bool operator==(const Ratio& lhs, const Ratio& rhs) noexcept {
    const auto lsimple = lhs.simplified();
    const auto rsimple = rhs.simplified();
    return lsimple.numerator == rsimple.numerator and lsimple.denominator == rsimple.denominator;
  }

  template<typename OType>
  friend
  constexpr
  auto operator<=>(const Ratio& lhs, const OType& rhs) noexcept {
    return static_cast<OType>(lhs) <=> rhs;
  }

  template<typename OType>
  friend
  constexpr
  bool operator==(const Ratio& lhs, const OType& rhs) noexcept {
    return static_cast<OType>(lhs) == rhs;
  }

  [[nodiscard]]
  friend
  constexpr
  Ratio operator+(const Ratio& ratio) noexcept {
    return { +ratio.numerator, +ratio.denominator };
  }

  [[nodiscard]]
  friend
  constexpr
  Ratio operator-(const Ratio& ratio) noexcept {
    return { -ratio.numerator, ratio.denominator };
  }

  [[nodiscard]]
  friend
  constexpr
  Ratio operator+(const Ratio& lhs, const Ratio& rhs) noexcept {
    const auto target = lcm(lhs.denominator, rhs.denominator);
    const auto lmul = target / lhs.denominator;
    const auto rmul = target / rhs.denominator;

    return { (lhs.numerator * lmul) + (rhs.numerator * rmul), target };
  }

  [[nodiscard]]
  friend
  constexpr
  Ratio operator-(const Ratio& lhs, const Ratio& rhs) noexcept {
    const auto target = lcm(lhs.denominator, rhs.denominator);
    const auto lmul = target / lhs.denominator;
    const auto rmul = target / rhs.denominator;

    return { (lhs.numerator * lmul) - (rhs.numerator * rmul), target };
  }

  [[nodiscard]]
  friend
  constexpr
  Ratio operator*(const Ratio& lhs, const Ratio& rhs) noexcept {
    return { lhs.numerator * rhs.numerator, lhs.denominator * rhs.denominator };
  }

  [[nodiscard]]
  friend
  constexpr
  Ratio operator/(const Ratio& lhs, const Ratio& rhs) noexcept {
    return lhs * rhs.invert();
  }

  template<typename OType>
  [[nodiscard]]
  friend
  constexpr
  Ratio operator+(const Ratio& ratio, const OType& value) noexcept {
    return { ratio.numerator + (ratio.denominator * value), ratio.denominator };
  }

  template<typename OType>
  [[nodiscard]]
  friend
  constexpr
  Ratio operator-(const Ratio& ratio, const OType& value) noexcept {
    return { ratio.numerator - (ratio.denominator * value), ratio.denominator };
  }

  template<typename OType>
  [[nodiscard]]
  friend
  constexpr
  Ratio operator*(const Ratio& ratio, const OType& value) noexcept {
    return { ratio.numerator * value, ratio.denominator };
  }

  template<typename OType>
  [[nodiscard]]
  friend
  constexpr
  Ratio operator/(const Ratio& ratio, const OType& value) noexcept {
    return { ratio.numerator, ratio.denominator * value };
  }

  constexpr
  void simplify() noexcept {
    const auto divisor = gcd();

    numerator /= divisor;
    denominator /= divisor;
  }

  [[nodiscard]]
  constexpr
  Ratio simplified() const noexcept {
    auto copy = *this;
    copy.simplify();
    return copy;
  }
};

} // namespace flp

template<typename Type>
struct std::formatter<flp::Ratio<Type>> {
  constexpr
  auto parse(std::format_parse_context& context) {
    auto iterator = context.begin();

    while (iterator != context.end() and *iterator != '}') {
      ++iterator;
    }

    //VERIFY(iterator == context.end() or *iterator == '}', "");

    return iterator;
  }

  constexpr
  auto format(const flp::Ratio<Type>& ratio, std::format_context& context) const {
    return std::format_to(context.out(), "({}/{})", ratio.numerator, ratio.denominator);
  }
};

template<typename OStream, typename Type>
OStream& operator<<(OStream& ostream, const flp::Ratio<Type>& ratio) {
  return ostream << std::format("{}", ratio);
}
