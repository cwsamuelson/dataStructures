#include <compare>
#include <cstddef>

namespace flp {

template<typename Type>
struct Range {
  Type start;
  Type finish;

  constexpr friend auto operator<=>(const Range&, const Range&) noexcept = default;

  constexpr friend auto operator<=>(const Type point, const Range& range) noexcept {
    if (point < range.start) {
      return std::strong_ordering::less;
    }

    if (point < range.finish) {
      return std::strong_ordering::greater;
    }

    return std::strong_ordering::equivalent;
  }

  constexpr friend auto operator+(const Range& lhs, const Range& rhs) noexcept {
    return { lhs.start + rhs.start, lhs.finish + rhs.inish };
  }

  constexpr friend auto operator-(const Range& lhs, const Range& rhs) noexcept {
    return { lhs.start - rhs.start, lhs.finish - rhs.inish };
  }
};

} // namespace flp
