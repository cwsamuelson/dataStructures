#pragma once

#include <array>
#include <concepts>
#include <cstddef>
#include <functional>
#include <initializer_list>
#include <ranges>

namespace flp {

template<typename Type, size_t Size>
struct Vec {
  constexpr Vec() = default;

  constexpr Vec(const Vec&)     = default;
  constexpr Vec(Vec&&) noexcept = default;

  constexpr Vec& operator=(const Vec&)     = default;
  constexpr Vec& operator=(Vec&&) noexcept = default;

  constexpr Vec(const Type& value) noexcept {
    for (auto& component : components) {
      component = value;
    }
  }

  constexpr Vec(std::array<Type, Size> array) noexcept
    : components(std::move(array)) {}

  template<typename Range>
  constexpr Vec(Range&& range) {
    for (const auto& [component, value] : std::views::zip(components, std::move(range))) {
      component = value;
    }
  }

  template<typename First, typename... Rest>
    requires((std::same_as<First, Rest> and ...) and sizeof...(Rest) + 1 == Size)
  constexpr Vec(First&& first, Rest&&... values) noexcept
    : components { std::forward<First>(first), std::forward<Rest>(values)... } {}

  ~Vec() = default;

  friend constexpr auto operator<=>(const Vec&, const Vec&) noexcept = default;

  constexpr decltype(auto) operator[](this auto&& self, const size_t index) {
    return self.components.at(index);
  }

  template<typename Functor>
  constexpr auto apply(Functor&& functor) {
    using FResult = decltype(functor(std::declval<Type>()));

    return Vec<FResult, Size> { components | std::views::transform(functor) | std::ranges::to<FResult>() };
  }

  std::array<Type, Size> components {};
};

template<typename Type, size_t Size, typename Functor>
constexpr auto combine(const Vec<Type, Size>& vec1, const Vec<Type, Size>& vec2, Functor&& functor) noexcept {
  using FResult = decltype(functor(std::declval<Type>(), std::declval<Type>()));

  return Vec<FResult, Size> { std::views::zip(vec1.components, vec2.components)
                              | std::views::transform([&functor](const auto& pair) {
                                  const auto& [x, y] = pair;
                                  return functor(x, y);
                                }) };
}

template<typename Type, size_t Size, typename Functor, std::floating_point FloatPt>
constexpr auto combine(const Vec<Type, Size>& vec, const FloatPt&& scalar, Functor&& functor) noexcept {
  using FResult = decltype(functor(std::declval<Type>(), std::declval<FloatPt>()));

  return Vec<FResult, Size> { vec | std::views::transform([&functor, &scalar](const auto& component) {
                                return functor(component, scalar);
                              }) };
}

template<typename Type, size_t Size, typename Functor, std::floating_point FloatPt>
constexpr auto combine(const FloatPt&& scalar, const Vec<Type, Size>& vec, Functor&& functor) noexcept {
  using FResult = decltype(functor(std::declval<FloatPt>(), std::declval<Type>()));

  return Vec<FResult, Size> { vec | std::views::transform([&functor, &scalar](const auto& component) {
                                return functor(scalar, component);
                              }) };
}

template<typename Type, size_t Size>
constexpr Vec<Type, Size> operator+(const Vec<Type, Size>& vec1, const Vec<Type, Size>& vec2) noexcept {
  return combine(vec1, vec2, std::plus<> {});
}

template<typename Type, size_t Size>
constexpr Vec<Type, Size> operator-(const Vec<Type, Size>& vec1, const Vec<Type, Size>& vec2) noexcept {
  return combine(vec1, vec2, std::minus<> {});
}

template<typename Type, size_t Size>
constexpr Vec<Type, Size> operator*(const Vec<Type, Size>& vec1, const Vec<Type, Size>& vec2) noexcept {
  return combine(vec1, vec2, std::multiplies<> {});
}

template<typename Type, size_t Size>
constexpr Vec<Type, Size> operator/(const Vec<Type, Size>& vec1, const Vec<Type, Size>& vec2) noexcept {
  return combine(vec1, vec2, std::divides<> {});
}

template<typename Type, size_t Size>
constexpr Vec<Type, Size> operator*(const std::floating_point auto& scalar, const Vec<Type, Size>& vec) noexcept {
  return combine(scalar, vec, std::multiplies<> {});
}

template<typename Type, size_t Size>
constexpr Vec<Type, Size> operator/(const std::floating_point auto& scalar, const Vec<Type, Size>& vec) noexcept {
  return combine(scalar, vec, std::divides<> {});
}

template<typename Type, size_t Size>
constexpr Vec<Type, Size> operator*(const Vec<Type, Size>& vec, const std::floating_point auto& scalar) noexcept {
  return combine(vec, scalar, std::multiplies<> {});
}

template<typename Type, size_t Size>
constexpr Vec<Type, Size> operator/(const Vec<Type, Size>& vec, const std::floating_point auto& scalar) noexcept {
  return combine(vec, scalar, std::divides<> {});
}

} // namespace flp
