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
    return RangedInt<WorstCaseRange<ValueRange, OtherRange, std::plus<>>::range, Policy>(std::plus {}(value, other.value), unconstrained);
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
  // perhaps it should return a rational?
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

// template<typename Type>
// RangedInt(const Type&) -> RangedInt<Range { std::numeric_limits<Type>::min(), std::numeric_limits<Type>::max() }>;

} // namespace flp

namespace std {

template<flp::Range range1, flp::Range range2, typename policy1, typename policy2>
struct common_type<flp::RangedInt<range1, policy1>, flp::RangedInt<range2, policy2>> {
  using type = flp::RangedInt<flp::CommonRange<range1, range2>::Value, policy1>;
};

template<flp::Range range, typename Policy>
struct numeric_limits<flp::RangedInt<range, Policy>> {
  // Member constants
  static constexpr bool is_specialized = true;
  static constexpr bool is_signed = range.start < 0;
  static constexpr bool is_integer = true;
  static constexpr bool is_exact = true;
  static constexpr bool has_infinity = false;
  // static constexpr bool has_quiet_NaN
  // static constexpr bool has_signaling_NaN
  // static constexpr bool has_denorm
  // static constexpr bool has_denorm_loss
  static constexpr std::float_round_style round_style = std::round_indeterminate; //!@TODO
  // static constexpr bool is_iec559
  // static constexpr bool is_bounded
  // static constexpr bool is_modulo
  // static constexpr size_t digits
  // static constexpr size_t digits10
  // static constexpr size_t max_digits10
  // static constexpr size_t radix
  // static constexpr size_t min_exponent
  // static constexpr size_t min_exponent10
  // static constexpr size_t max_exponent
  // static constexpr size_t max_exponent10
  static constexpr bool traps = true; //!@TODO: determining if 'traps' is less trivial than it sounds.
  static constexpr bool tinyness_before = false;

  // Member functions
  [[nodiscard]]
  static constexpr
  flp::RangedInt<range, Policy> min() noexcept {
    return range.start;
  }

  [[nodiscard]]
  static constexpr
  flp::RangedInt<range, Policy> lowest() noexcept {
    return range.start;
  }

  [[nodiscard]]
  static constexpr
  flp::RangedInt<range, Policy> max() noexcept {
    return range.finish;
  }

  //!@NOTE By its definition this one is a bit weird.  'the difference between
  // 1.0 and the next value representable by the floating-point type `T`'.
  // `RangedInt` isn't floating point, so this value should be '0'.  But '0' may
  // not always be valid; 0 may not be in the range!  It is specified that this
  // function is only meaningful if `is_integer == false`, which may mean it's
  // allowed to not exist.  This would be optimal since returning `0` may cause
  // an exception to be thrown, depending on the `Policy` type.
  // [[nodiscard]]
  // static constexpr
  // flp::RangedInt<range, Policy> epsilon() noexcept {
  //   return 0;
  // }

  //!@NOTE See note for `epsilon()`
  // [[nodiscard]]
  // static constexpr
  // flp::RangedInt<range, Policy> round_error() noexcept {
  //   return 0;
  // }

  //!@NOTE See note for `epsilon()`; except this function may not need to exist
  //since `has_infinity` will (likely) be false.
  // [[nodiscard]]
  // static constexpr
  // flp::RangedInt<range, Policy> infinity() noexcept {
  //   return 0;
  // }

  //!@NOTE See note for `epsilon()`
  // [[nodiscard]]
  // static constexpr
  // flp::RangedInt<range, Policy> quiet_NaN() noexcept {
  // }

  //!@NOTE See note for `epsilon()`
  // [[nodiscard]]
  // static constexpr
  // flp::RangedInt<range, Policy> signaling_NaN() noexcept {
  // }

  [[nodiscard]]
  static constexpr
  flp::RangedInt<range, Policy> denorm_min() noexcept {
    return min();
  }
};

} // namespace std
