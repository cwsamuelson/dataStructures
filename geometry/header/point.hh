#pragma once

#include <algorithm>

namespace flp {

template<typename Type = float>
struct Point {
  Type x{};
  Type y{};

  [[nodiscard]]
  constexpr
  Point center() const noexcept {
    return *this;
  }

  friend
  constexpr
  auto operator<=>(const Point&, const Point&) noexcept = default;

  friend
  constexpr
  bool operator==(const Point&, const Point&) noexcept = default;
};

} // namespace flp
