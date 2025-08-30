#pragma once

#include "vec.hh"
#include "vector.hh"

#include <concepts>
#include <cstddef>

namespace flp {

template<typename Type, size_t Size>
struct Point {
  constexpr
  Point() noexcept = default;

  constexpr
  Point(const Type& value) noexcept
    : vec(value)
  {}

  template<typename First, typename ...Rest>
    requires ((std::same_as<First, Rest> and ...) and sizeof...(Rest) + 1 == Size)
  constexpr
  Point(First&& first, Rest&& ...values) noexcept
    : vec{ std::forward<First>(first), std::forward<Rest>(values)... }
  {}

  constexpr
  Point(const Vec<Type, Size>& v)
    : vec(v)
  {}

  friend constexpr auto operator<=>(const Point&, const Point&) noexcept = default;

  constexpr
  decltype(auto) operator[](this auto&& self, const size_t index) {
    return self.vec.at(index);
  }

  Vec<Type, Size> vec;
};

template<typename Type, size_t Size>
constexpr
Point<Type, Size> operator+(const Point<Type, Size>& point, const Vector<Type, Size>& vector) noexcept {
  return point.vec + vector.vec;
}

template<typename Type, size_t Size>
constexpr
Vector<Type, Size> operator-(const Point<Type, Size>& point1, const Point<Type, Size>& point2) noexcept {
  return point1.vec - point2.vec;
}

}
