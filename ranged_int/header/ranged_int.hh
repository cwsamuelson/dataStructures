#pragma once

#include "deduced_type.hh"
#include "policies.hh"
#include "worst_case.hh"

#include <core/range.hh>

#include <error_help.hh>

#include <algorithm>
#include <limits>
#include <type_traits>

namespace flp {

struct Unconstrained_t {};
constexpr static Unconstrained_t unconstrained{};

template<BoundRange ValueRange, typename Policy = ErrorPolicy>
struct RangedInt {
  using Type                  = DeducedType<ValueRange>;
  static constexpr auto range = ValueRange;
  static constexpr Policy policy{};

  Type value = ValueRange.start;

  constexpr
  RangedInt() noexcept = default;

  template<typename InputType>
  constexpr
  RangedInt(const InputType& input)
    : value(input) {
    VERIFY(input >= ValueRange.start and input <= ValueRange.finish, "Value({}) doesn't fit in range.", input);
  }

  template<BoundRange OtherRange, typename OtherPolicy>
    requires (OtherRange.start >= ValueRange.start and OtherRange.finish <= ValueRange.finish)
  constexpr
  RangedInt operator=(const RangedInt<OtherRange, OtherPolicy>& other) noexcept {
    VERIFY(other.value >= ValueRange.start and other.value <= ValueRange.finish, "Value({}) doesn't fit in range.", other.value);

    value = other.value;

    return *this;
  }

  template<BoundRange range, typename OtherPolicy>
  constexpr friend
  auto operator<=>(const RangedInt& lhs, const RangedInt<range, OtherPolicy>& rhs) noexcept {
    return lhs.value <=> rhs.value;
  }

  template<std::integral Other>
  constexpr friend
  auto operator<=>(const RangedInt& lhs, const Other& rhs) noexcept {
    return lhs.value <=> rhs;
  }

  template<BoundRange range, typename OtherPolicy>
  constexpr friend
  bool operator==(const RangedInt& lhs, const RangedInt<range, OtherPolicy>& rhs) noexcept {
    return lhs.value == rhs.value;
  }

  template<std::integral Other>
  constexpr friend
  bool operator==(const RangedInt& lhs, const Other& rhs) noexcept {
    return lhs.value == rhs;
  }

  template<BoundRange OtherRange, typename OtherPolicy>
  constexpr
  auto operator+(const RangedInt<OtherRange, OtherPolicy>& other) const noexcept {
    return RangedInt<WorstCaseRange<ValueRange, OtherRange, std::plus<>>::range, Policy>(std::plus {}(value, other.value), unconstrained);
  }

  template<BoundRange OtherRange, typename OtherPolicy>
  constexpr
  auto operator-(const RangedInt<OtherRange, OtherPolicy>& other) const noexcept {
    return RangedInt<WorstCaseRange<ValueRange, OtherRange, std::minus<>>::range, Policy>(std::minus {}(value, other.value),
                                                                                  unconstrained);
  }

  template<BoundRange OtherRange, typename OtherPolicy>
  constexpr
  auto operator*(const RangedInt<OtherRange, OtherPolicy>& other) const noexcept {
    return RangedInt<WorstCaseRange<ValueRange, OtherRange, std::multiplies<>>::range, Policy>(
      std::multiplies<> {}(value, other.value), unconstrained);
  }

  // the problem with integer division, is that the result is not even remotely likely to be integral
  /*template<BoundRange OtherRange, typename OtherPolicy>
  constexpr
  auto operator/(const RangedInt<OtherRange, OtherPolicy>& other) const noexcept {
    return RangedInt<ValueRange / OtherRange>(value / other, unconstrained);
  }*/

private:
  template<BoundRange OtherRange, typename OtherPolicy>
  friend struct RangedInt;

  constexpr RangedInt(const Type input, Unconstrained_t)
    : value(input)
  {}
};

// template<typename Type>
// RangedInt(const Type&) -> RangedInt<BoundRange { std::numeric_limits<Type>::min(), std::numeric_limits<Type>::max() }>;

} // namespace flp

namespace std {

template<flp::BoundRange range1, flp::BoundRange range2, typename policy1, typename policy2>
struct common_type<flp::RangedInt<range1, policy1>, flp::RangedInt<range2, policy2>> {
  using type = flp::RangedInt<flp::CommonRange<range1, range2>::Value, policy1>;
};

} // namespace std
