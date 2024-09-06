#pragma once

#include <error_help.hh>

#include <core/range.hh>

#include <limits>

namespace flp {

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

template<Range range>
using DeducedType = typename DeducedTypeImpl<range>::type;

template<Range ValueRange>
struct RangedInt {
  using Type = DeducedType<ValueRange>;

  Type value;

  template<typename InputType>
  constexpr RangedInt(const InputType& input)
    : value(input) {}

  template<Range OtherRange>
  constexpr RangedInt operator=(const RangedInt<OtherRange>& other) noexcept {
    VERIFY(OtherRange.start >= ValueRange.start and OtherRange.finish <= ValueRange.finish,
           "Incompatible ranges for assignment");

    value = other.value;

    return *this;
  }

  template<Range OtherRange>
  constexpr auto operator+(const RangedInt<OtherRange>& other) noexcept {
    return RangedInt<ValueRange + OtherRange>(value + other);
  }

  template<Range OtherRange>
  constexpr auto operator-(const RangedInt<OtherRange>& other) noexcept {
    return RangedInt<ValueRange - OtherRange>(value - other);
  }

  template<Range OtherRange>
  constexpr auto operator*(const RangedInt<OtherRange>& other) noexcept {
    return RangedInt<ValueRange * OtherRange>(value * other);
  }

  template<Range OtherRange>
  constexpr auto operator/(const RangedInt<OtherRange>& other) noexcept {
    return RangedInt<ValueRange / OtherRange>(value / other);
  }
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
