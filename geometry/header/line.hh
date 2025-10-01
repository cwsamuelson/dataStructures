#pragma once

#include <point.hh>

#include <algorithm>
#include <cmath>
#include <ranges>
#include <vector>

namespace flp {

template<typename Type = float>
struct Line {
  Point<Type> first{};
  Point<Type> second{};

  friend
  constexpr
  bool operator==(const Line&, const Line&) noexcept = default;
};

template<typename Type = float>
struct Segment {
  Point<Type> first{};
  Point<Type> second{};

  constexpr
  Type length() const noexcept {
    const auto [xmin, xmax] = std::minmax(first.x, second.x);
    const auto [ymin, ymax] = std::minmax(first.y, second.y);
    const auto dx = xmax - xmin;
    const auto dy = ymax - ymin;

    return std::sqrt((dx * dx) + (dy * dy));
  }

  friend
  constexpr
  bool operator==(const Segment&, const Segment&) noexcept = default;
};

template<typename Type = float>
struct PolyLine {
  std::vector<Point<Type>> points;

  constexpr
  Type length() const noexcept {
    Type total_length{};
    for (const auto& ptpair : points | std::views::slide(2)) {
      // std::accumulate?
      total_length += Segment<Type>{ptpair[0], ptpair[1]}.length();
    }
  }

  friend
  constexpr
  bool operator==(const PolyLine&, const PolyLine&) noexcept = default;
};

} // namespace flp
