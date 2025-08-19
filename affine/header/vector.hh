#pragma once

#include "vec.hh"

#include <concepts>
#include <cstddef>
#include <ranges>

namespace flp {

template<typename Type, size_t Size>
struct Vector {
  constexpr
  Vector() = default;

  constexpr
  Vector(const Type& value) noexcept
    : vec(value)
  {}

  template<typename First, typename ...Rest>
    requires ((std::same_as<First, Rest> and ...) and sizeof...(Rest) + 1 == Size)
  constexpr
  Vector(First&& first, Rest&& ...values) noexcept
    : vec{ std::forward<First>(first), std::forward<Rest>(values)... }
  {}

  friend constexpr auto operator<=>(const Vector&, const Vector&) noexcept = default;

  Vec<Type, Size> vec;
};

template<typename Type, size_t Size>
constexpr
Vector<Type, Size> operator+(const Vector<Type, Size>& vec1, const Vector<Type, Size>& vec2) noexcept {
  Vector<Type, Size> result;

  for (const auto& [r, c1, c2] : std::views::zip(result, vec1, vec2)) {
    r = c1 + c2;
  }

  return result;
}

template<typename Type, size_t Size>
constexpr
Vector<Type, Size> operator-(const Vector<Type, Size>& vec1, const Vector<Type, Size>& vec2) noexcept {
  Vector<Type, Size> result;

  for (const auto& [r, c1, c2] : std::views::zip(result, vec1, vec2)) {
    r = c1 - c2;
  }

  return result;
}

template<typename Type, size_t Size>
constexpr
Vector<Type, Size> operator*(const Vector<Type, Size>& vector, const std::floating_point auto& scalar) noexcept {
  Vector<Type, Size> result;

  for (const auto& [r, component] : std::views::zip(result, vector)) {
    r = component * scalar;
  }

  return result;
}

template<typename Type, size_t Size>
constexpr
Vector<Type, Size> operator*(const std::floating_point auto& scalar, const Vector<Type, Size>& vector) noexcept {
  Vector<Type, Size> result;

  for (const auto& [r, component] : std::views::zip(result, vector)) {
    r = component * scalar;
  }

  return result;
}

template<typename Type, size_t Size>
constexpr
Vector<Type, Size> operator/(const Vector<Type, Size>& vector, const std::floating_point auto& scalar) noexcept {
  Vector<Type, Size> result;

  for (const auto& [r, component] : std::views::zip(result, vector)) {
    r = component / scalar;
  }

  return result;
}

template<typename Type, size_t Size>
constexpr
Vector<Type, Size> operator/(const std::floating_point auto& scalar, const Vector<Type, Size>& vector) noexcept {
  Vector<Type, Size> result;

  for (const auto& [r, component] : std::views::zip(result, vector)) {
    r = component / scalar;
  }

  return result;
}

template<typename Type, size_t Size>
constexpr
float magnitude(const Vector<Type, Size>&) noexcept;

// while a vector of any type may be provided, only float is ever returned.
// While perhaps not precisely the best choice, an integral result does not
// make sense, even when the input vector is integral itself, since
// `magnitude(normalize(Vector<int>(1, 1)))` would result in
// `sqrt(2), or 1.4...`, which is certainly not normalized, and any solution
// that results in `magnitude(normalize(Vector<int>(1, 1))) == 1` would result
// in at least one component that is non-integral.
// With that in mind, I'm still unsure that `float` is correct.  `double` may
// be correct, or perhaps some other context-sensitive type (i.e. `complex` etc).
// For now I make no attempt to 'calculate' what the result type should be,
// instead simply providing it as a parameter such that the user may specify it.
template<typename Type, size_t Size, typename Result = float>
constexpr
Vector<Result, Size> normalize(const Vector<Type, Size>& vector) noexcept {
  return vector / magnitude(vector);
}

template<typename Type, size_t Size>
constexpr
Type dot(const Vector<Type, Size>& vec1, const Vector<Type, Size>& vec2) noexcept {
  Type result;

  for (const auto& [c1, c2] : std::views::zip(vec1.components, vec1.components)) {
    result += c1 * c2;
  }

  return result;
}

// turns out cross-product only applies to 3D and **7D**??
template<typename Type>
constexpr Vector<Type, 3> cross(const Vector<Type, 3>& vec1, const Vector<Type, 3>& vec2) noexcept {
  return Vector<Type, 3>(
    vec1.components[1] * vec2.components[2] - vec1.components[2] * vec2.components[1],
    vec1.components[2] * vec2.components[0] - vec1.components[0] * vec2.components[2],
    vec1.components[0] * vec2.components[1] - vec1.components[1] * vec2.components[0]
  );
}

}
