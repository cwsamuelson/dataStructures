#pragma once

#include <compare>
#include <utility>

namespace flp {

template<typename Type>
struct Range {
  Type start;
  Type finish;

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

  constexpr friend auto operator+(const Range& lhs, const Range& rhs) noexcept {
    return { lhs.start + rhs.start, lhs.finish + rhs.finish };
  }

  constexpr friend auto operator-(const Range& lhs, const Range& rhs) noexcept {
    return { lhs.start - rhs.start, lhs.finish - rhs.finish };
  }
};

} // namespace flp
