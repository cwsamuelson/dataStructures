#pragma once

#include <error_help.hh>

#include <core/range.hh>

#include <algorithm>
#include <limits>
#include <type_traits>

namespace flp {

namespace {

template<Range>
struct DeducedTypeImpl;

template<Range range>
  requires(range.start >= 0 and range.finish <= 255)
struct DeducedTypeImpl<range> {
  using type = uint8_t;
};

template<Range range>
  requires(range.start >= 0 and range.finish <= 65535 and range.finish > 255)
struct DeducedTypeImpl<range> {
  using type = uint16_t;
};

template<Range range>
  requires(range.start >= 0 and range.finish <= std::numeric_limits<uint32_t>::max() and range.finish > 65535)
struct DeducedTypeImpl<range> {
  using type = uint32_t;
};

template<Range range>
  requires(range.start >= 0 and range.finish <= std::numeric_limits<uint64_t>::max()
           and range.finish > std::numeric_limits<uint32_t>::max())
struct DeducedTypeImpl<range> {
  using type = uint64_t;
};

template<Range range>
  requires(range.start < 0 and range.start >= std::numeric_limits<int8_t>::min()
           and range.finish <= std::numeric_limits<int8_t>::max())
struct DeducedTypeImpl<range> {
  using type = int8_t;
};

template<Range range>
  requires(range.start < 0 and range.start >= std::numeric_limits<int16_t>::min()
           and range.finish <= std::numeric_limits<int16_t>::max()
           and (range.start<std::numeric_limits<int8_t>::min() or range.finish> std::numeric_limits<int8_t>::max()))
struct DeducedTypeImpl<range> {
  using type = int16_t;
};

template<Range range>
  requires(range.start < 0 and range.start >= std::numeric_limits<int32_t>::min()
           and range.finish <= std::numeric_limits<int32_t>::max()
           and (range.start<std::numeric_limits<int16_t>::min() or range.finish> std::numeric_limits<int16_t>::max()))
struct DeducedTypeImpl<range> {
  using type = int32_t;
};

template<Range range>
  requires(range.start < 0 and range.start >= std::numeric_limits<int64_t>::min()
           and range.finish <= std::numeric_limits<int64_t>::max()
           and (range.start<std::numeric_limits<int32_t>::min() or range.finish> std::numeric_limits<int32_t>::max()))
struct DeducedTypeImpl<range> {
  using type = int64_t;
};

template<Range op1_range, Range op2_range, typename Op>
struct WorstCaseRange {
  constexpr static std::array values { Op {}(op1_range.start, op2_range.start),
                                       Op {}(op1_range.start, op2_range.finish),
                                       Op {}(op1_range.finish, op2_range.start),
                                       Op {}(op1_range.finish, op2_range.finish) };
  constexpr static Range      range = {
    *std::ranges::min_element(values),
    *std::ranges::max_element(values),
  };
};

} // namespace

template<Range range>
using DeducedType = typename DeducedTypeImpl<range>::type;

struct Unconstrained_t {};
constexpr static Unconstrained_t unconstrained {};

template<Range ValueRange>
struct RangedInt {
  using Type                  = DeducedType<ValueRange>;
  constexpr static auto range = ValueRange;

  Type value = ValueRange.start;

  constexpr RangedInt() noexcept = default;

  template<typename InputType>
  constexpr RangedInt(const InputType& input)
    : value(input) {
    VERIFY(input >= ValueRange.start and input <= ValueRange.finish, "");
  }

  template<Range OtherRange>
  constexpr RangedInt operator=(const RangedInt<OtherRange>& other) noexcept {
    VERIFY(OtherRange.start >= ValueRange.start and OtherRange.finish <= ValueRange.finish,
           "Incompatible ranges for assignment");

    value = other.value;

    VERIFY(other.value >= ValueRange.start and other.value <= ValueRange.finish, "");

    return *this;
  }

  template<Range OtherRange>
  constexpr auto operator+(const RangedInt<OtherRange>& other) noexcept {
    return RangedInt<WorstCaseRange<ValueRange, OtherRange, std::plus<>>::range>(std::plus<> {}(value, other.value),
                                                                                 unconstrained);
  }

  template<Range OtherRange>
  constexpr auto operator-(const RangedInt<OtherRange>& other) noexcept {
    return RangedInt<WorstCaseRange<ValueRange, OtherRange, std::minus<>>::range>(std::minus {}(value, other.value),
                                                                                  unconstrained);
  }

  template<Range OtherRange>
  constexpr auto operator*(const RangedInt<OtherRange>& other) noexcept {
    return RangedInt<WorstCaseRange<ValueRange, OtherRange, std::multiplies<>>::range>(
      std::multiplies<> {}(value, other.value), unconstrained);
  }

  // the problem with integer division, is that the result is not even remotely likely to be integral
  /*template<Range OtherRange>
  constexpr auto operator/(const RangedInt<OtherRange>& other) noexcept {
    return RangedInt<ValueRange / OtherRange>(value / other, unconstrained);
  }*/

private:
  template<Range OtherRange>
  friend struct RangedInt;

  constexpr RangedInt(const Type input, Unconstrained_t)
    : value(input) {}
};

template<typename Type>
RangedInt(const Type&) -> RangedInt<Range { std::numeric_limits<Type>::min(), std::numeric_limits<Type>::max() }>;

using u8  = RangedInt<{ std::numeric_limits<uint8_t>::min(), std::numeric_limits<uint8_t>::max() }>;
using u16 = RangedInt<{ std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max() }>;
using u32 = RangedInt<{ std::numeric_limits<uint32_t>::min(), std::numeric_limits<uint32_t>::max() }>;
using u64 = RangedInt<{ std::numeric_limits<uint64_t>::min(), std::numeric_limits<uint64_t>::max() }>;
using s8  = RangedInt<{ std::numeric_limits<int8_t>::min(), std::numeric_limits<int8_t>::max() }>;
using s16 = RangedInt<{ std::numeric_limits<int16_t>::min(), std::numeric_limits<int16_t>::max() }>;
using s32 = RangedInt<{ std::numeric_limits<int32_t>::min(), std::numeric_limits<int32_t>::max() }>;
using s64 = RangedInt<{ std::numeric_limits<int64_t>::min(), std::numeric_limits<int64_t>::max() }>;

} // namespace flp

namespace std {

template<flp::Range range1, flp::Range range2>
struct common_type<flp::RangedInt<range1>, flp::RangedInt<range2>> {
  using type = flp::RangedInt<flp::CommonRange<range1, range2>::Value>;
};

} // namespace std
