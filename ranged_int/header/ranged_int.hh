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

template<Range ValueRange, typename Policy = ErrorPolicy>
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

  template<Range OtherRange, typename OtherPolicy>
    requires (OtherRange.start >= ValueRange.start and OtherRange.finish <= ValueRange.finish)
  constexpr
  RangedInt operator=(const RangedInt<OtherRange, OtherPolicy>& other) noexcept {
    VERIFY(other.value >= ValueRange.start and other.value <= ValueRange.finish, "Value({}) doesn't fit in range.", other.value);

    value = other.value;

    return *this;
  }

  template<Range range, typename OtherPolicy>
  constexpr friend
  auto operator<=>(const RangedInt& lhs, const RangedInt<range, OtherPolicy>& rhs) noexcept {
    return lhs.value <=> rhs.value;
  }

  template<std::integral Other>
  constexpr friend
  auto operator<=>(const RangedInt& lhs, const Other& rhs) noexcept {
    return lhs.value <=> rhs;
  }

  template<Range range, typename OtherPolicy>
  constexpr friend
  bool operator==(const RangedInt& lhs, const RangedInt<range, OtherPolicy>& rhs) noexcept {
    return lhs.value == rhs.value;
  }

  template<std::integral Other>
  constexpr friend
  bool operator==(const RangedInt& lhs, const Other& rhs) noexcept {
    return lhs.value == rhs;
  }

  template<Range OtherRange, typename OtherPolicy>
  constexpr
  auto operator+(const RangedInt<OtherRange, OtherPolicy>& other) const noexcept {
    using WorstCase = WorstCaseRange<ValueRange, OtherRange, std::plus<>>;
    using MathType = typename WorstCase::Type;
    return RangedInt<WorstCase::range, Policy>(std::plus<MathType> {}(value, other.value), unconstrained);
  }

  template<Range OtherRange, typename OtherPolicy>
  constexpr
  auto operator-(const RangedInt<OtherRange, OtherPolicy>& other) const noexcept {
    return RangedInt<WorstCaseRange<ValueRange, OtherRange, std::minus<>>::range, Policy>(std::minus {}(value, other.value),
                                                                                  unconstrained);
  }

  template<Range OtherRange, typename OtherPolicy>
  constexpr
  auto operator*(const RangedInt<OtherRange, OtherPolicy>& other) const noexcept {
    return RangedInt<WorstCaseRange<ValueRange, OtherRange, std::multiplies<>>::range, Policy>(
      std::multiplies<> {}(value, other.value), unconstrained);
  }

  // the problem with integer division, is that the result is not even remotely likely to be integral
  /*template<Range OtherRange, typename OtherPolicy>
  constexpr
  auto operator/(const RangedInt<OtherRange, OtherPolicy>& other) const noexcept {
    return RangedInt<ValueRange / OtherRange>(value / other, unconstrained);
  }*/

private:
  template<Range OtherRange, typename OtherPolicy>
  friend struct RangedInt;

  constexpr RangedInt(const Type input, Unconstrained_t)
    : value(input)
  {}
};

template<typename Type, typename Policy>
RangedInt(const Type&) -> RangedInt<Range { std::numeric_limits<Type>::min(), std::numeric_limits<Type>::max() }, Policy>;

} // namespace flp

namespace std {

template<flp::Range range1, flp::Range range2, typename policy1, typename policy2>
struct common_type<flp::RangedInt<range1, policy1>, flp::RangedInt<range2, policy2>> {
  using type = flp::RangedInt<flp::CommonRange<range1, range2>::Value, policy1>;
};

} // namespace std
