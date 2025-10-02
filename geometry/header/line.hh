#pragma once

#include <point.hh>

#include <algorithm>
#include <cmath>
#include <limits>
#include <ranges>
#include <vector>

namespace flp {

template<typename Type = float>
struct Line {
  Point<Type> first{};
  Point<Type> second{};

  [[nodiscard]]
  constexpr
  Point<Type> center() const noexcept {
    if (vertical()) {
      return {first.x, 0};
    }

    return {0, first.y - (slope() * first.x)};
  }

  [[nodiscard]]
  constexpr
  Type length() const noexcept {
    return std::numeric_limits<Type>::infinity();
  }

  [[nodiscard]]
  constexpr
  Type slope() const noexcept {
    if (vertical()) {
      return std::numeric_limits<Type>::infinity();
    }

    return (second.y - first.y) / (second.x - first.x);
  }

  [[nodiscard]]
  constexpr
  bool contains(const Point<Type>& point) const noexcept {
    return (point.x * slope()) + center().y == point.y;
  }

  [[nodiscard]]
  constexpr
  bool vertical() const noexcept {
    return first.x == second.x;
  }

  // parallel

  [[nodiscard]]
  friend
  constexpr
  bool operator==(const Line&, const Line&) noexcept = default;

  [[nodiscard]]
  friend
  constexpr
  auto operator<=>(const Line& line, const Point<Type>& point) noexcept {
    const auto target = line.slope() * point.x + line.center().y;
    return target <=> point.y;
  }
};

template<typename Type = float>
struct Segment {
  Point<Type> first{};
  Point<Type> second{};

  [[nodiscard]]
  constexpr
  Point<Type> center() const noexcept {
    return {first.x + ((second.x - first.x) / 2), first.y + ((second.y - first.y) / 2)};
  }

  [[nodiscard]]
  constexpr
  Type length() const noexcept {
    const auto [xmin, xmax] = std::minmax(first.x, second.x);
    const auto [ymin, ymax] = std::minmax(first.y, second.y);
    const auto dx = xmax - xmin;
    const auto dy = ymax - ymin;

    return std::sqrt((dx * dx) + (dy * dy));
  }

  [[nodiscard]]
  constexpr
  Type slope() const noexcept {
    if (vertical()) {
      return std::numeric_limits<Type>::infinity();
    }

    return (second.y - first.y) / (second.x - first.x);
  }

  [[nodiscard]]
  constexpr
  bool contains(const Point<Type>& point) const noexcept {
    if (vertical() and point.x == first.x) {
      return point.y >= first.y and point.y <= second.y;
    }

    return point.x >= first.x and point.x <= second.x and ((point.x * slope()) + center().y) == point.y;
  }

  [[nodiscard]]
  constexpr
  bool vertical() const noexcept {
    return first.x == second.x;
  }

  [[nodiscard]]
  friend
  constexpr
  bool operator==(const Segment&, const Segment&) noexcept = default;
};

template<typename Type = float>
struct PolyLine {
  std::vector<Point<Type>> points;

  [[nodiscard]]
  constexpr
  Point<Type> center() const noexcept {
    auto centers = points
    | std::views::transform([](const auto& point) {
      return point.center();
    });
    auto psum = std::ranges::fold_left(centers, Point<Type>{}, [](const auto& lpoint, const auto& rpoint) {
      return {lpoint.x + rpoint.x, lpoint.y + rpoint.y};
    });

    return {psum.x / points.size(), psum.y / points.size()};
  }

  [[nodiscard]]
  constexpr
  Type length() const noexcept {
    Type total_length{};
    for (const auto& ptpair : points | std::views::slide(2)) {
      // std::accumulate?
      total_length += Segment<Type>{ptpair[0], ptpair[1]}.length();
    }
  }

  [[nodiscard]]
  friend
  constexpr
  bool operator==(const PolyLine&, const PolyLine&) noexcept = default;
};

template<typename Type>
struct Ray {
  Point<Type> start;
  Point<Type> direction;

  [[nodiscard]]
  constexpr
  Type length() const noexcept {
    return std::numeric_limits<Type>::infinity();
  }

  [[nodiscard]]
  friend
  constexpr
  bool operator==(const Ray&, const Ray&) noexcept = default;
};

} // namespace flp
