#pragma once


namespace flp {

template<typename Type = float>
struct Point {
  Type x{};
  Type y{};

  friend
  constexpr
  auto operator<=>(const Point&, const Point&) noexcept = default;
  friend
  constexpr
  bool operator==(const Point&, const Point&) noexcept = default;
};

} // namespace flp
