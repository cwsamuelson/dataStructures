#pragma once

#include <compare>
#include <utility>

namespace flp {

template<typename Type>
struct Range {
  // signed for negative ranges
  // but now half of the 64-bit range is unavailable
  // using Type = signed long long;
  Type start;
  Type finish;

  constexpr  Range() noexcept             = default;
  constexpr  Range(const Range&) noexcept = default;
  constexpr  Range(Range&&) noexcept      = default;
  constexpr ~Range() noexcept             = default;

  constexpr Range& operator=(const Range&) noexcept = default;
  constexpr Range& operator=(Range&&) noexcept      = default;

  constexpr Range(const Type range_start, const Type range_finish)
    : start(range_start)
    , finish(range_finish) {}

  constexpr friend auto operator<=>(const Range&, const Range&) noexcept = default;
  constexpr friend bool operator==(const Range&, const Range&) noexcept  = default;

  constexpr friend auto operator<=>(const auto point, const Range& range) noexcept {
    if (std::cmp_less(point, range.start)) {
      return std::strong_ordering::less;
    }

    if (std::cmp_greater(point, range.finish)) {
      return std::strong_ordering::greater;
    }

    return std::strong_ordering::equivalent;
  }
  constexpr friend bool operator==(const auto point, const Range& range) noexcept {
    return std::cmp_greater_equal(point, range.start) and std::cmp_less_equal(point, range.finish);
  }

  constexpr friend Range operator+(const Range& lhs, const Range& rhs) noexcept {
    return { lhs.start + rhs.start, lhs.finish + rhs.finish };
  }

  constexpr friend Range operator-(const Range& lhs, const Range& rhs) noexcept {
    return { lhs.start - rhs.start, lhs.finish - rhs.finish };
  }
};

// based on common_type
// Value is a range that both given ranges could fit into
template<Range range1, Range range2>
struct CommonRange {
  constexpr static auto Value = Range { std::min(range1.start, range2.start), std::max(range1.finish, range2.finish) };
};

template<Range range>
constexpr static bool IsNegative = range.start < 0;

} // namespace flp
