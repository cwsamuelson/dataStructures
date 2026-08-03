#pragma once

#include "shapes/swizzle.hh"

#include <core/concepts.hh>

#include <array>
#include <concepts>
#include <cstddef>
#include <format>
#include <utility>

namespace flp {

// GLSL-like vecN type.  Math operations are member-wise
template<typename Type, size_t Count>
struct vecn {
  static_assert(sizeof(Type) * Count);

  constexpr vecn() noexcept
    : values {} {}

  constexpr vecn(const Type& value)
    : values {} {
    values.fill(value);
  }

  template<std::same_as<Type>... T>
    requires(sizeof...(T) == Count)
  constexpr vecn(const T&... Values) noexcept
    : values { Values... } {}

  constexpr vecn(const std::array<Type, Count>& input)
    : values(input) {}

  template<typename OType, size_t OCount, size_t... Indices>
  constexpr vecn(const Swizzle<vecn<OType, OCount>, Type, Indices...>& swiz)
    : vecn(static_cast<std::array<Type, Count>>(swiz)) {}

  constexpr vecn(std::initializer_list<Type> il) {
    for (size_t index {}; auto& value : il) {
      values.at(index++) = value;
    }
  }

  constexpr vecn(const vecn&) noexcept = default;

  constexpr vecn(vecn&&) noexcept = default;

  constexpr vecn& operator=(const vecn&) noexcept = default;

  constexpr vecn& operator=(vecn&&) noexcept = default;

  constexpr friend vecn operator+(const vecn& vec) noexcept {
    auto posate = []<size_t... Indices>(const vecn& vec, std::integer_sequence<size_t, Indices...>) noexcept {
      return vecn { +vec.values[Indices]... };
    };

    return posate(vec, std::make_integer_sequence<size_t, Count>());
  }

  constexpr friend vecn operator-(const vecn& vec) noexcept {
    auto negate = []<size_t... Indices>(const vecn& vec, std::integer_sequence<size_t, Indices...>) noexcept {
      return vecn { -vec.values[Indices]... };
    };

    return negate(vec, std::make_integer_sequence<size_t, Count>());
  }

  constexpr vecn& operator+=(const vecn& other) noexcept {
    [this]<size_t... Indices>(const vecn& vec, std::integer_sequence<size_t, Indices...>) noexcept {
      ((values[Indices] += vec.values[Indices]), ...);
    }(other, std::make_integer_sequence<size_t, Count>());

    return *this;
  }

  constexpr vecn& operator-=(const vecn& other) noexcept {
    [this]<size_t... Indices>(const vecn& vec, std::integer_sequence<size_t, Indices...>) noexcept {
      ((values[Indices] -= vec.values[Indices]), ...);
    }(other, std::make_integer_sequence<size_t, Count>());

    return *this;
  }

  constexpr vecn& operator*=(const vecn& other) noexcept {
    [this]<size_t... Indices>(const vecn& other, std::integer_sequence<size_t, Indices...>) noexcept {
      ((values[Indices] *= other.values[Indices]), ...);
    }(other, std::make_integer_sequence<size_t, Count>());

    return *this;
  }

  constexpr vecn& operator/=(const vecn& other) noexcept {
    [this]<size_t... Indices>(const vecn& other, std::integer_sequence<size_t, Indices...>) noexcept {
      ((values[Indices] /= other.values[Indices]), ...);
    }(other, std::make_integer_sequence<size_t, Count>());

    return *this;
  }

  template<typename Other>
    requires(std::is_arithmetic_v<Other>)
  constexpr friend vecn& operator*=(vecn& vec, const Other& value) noexcept {
    [&vec]<size_t... Indices>(const auto& value, std::integer_sequence<size_t, Indices...>) noexcept {
      ((vec.values[Indices] *= value), ...);
    }(value, std::make_integer_sequence<size_t, Count>());

    return vec;
  }

  template<typename Other>
    requires(std::is_arithmetic_v<Other>)
  constexpr friend vecn& operator/=(vecn& vec, const Other& value) noexcept {
    [&vec]<size_t... Indices>(const auto& value, std::integer_sequence<size_t, Indices...>) noexcept {
      ((vec.values[Indices] /= value), ...);
    }(value, std::make_integer_sequence<size_t, Count>());

    return vec;
  }

  friend constexpr vecn operator+(const vecn& lhs, const vecn& rhs) noexcept {
    vecn other = lhs;
    return other += rhs;
  }

  friend constexpr vecn operator-(const vecn& lhs, const vecn& rhs) noexcept {
    vecn other = lhs;
    return other -= rhs;
  }

  friend constexpr vecn operator*(const vecn& lhs, const vecn& rhs) noexcept {
    vecn other = lhs;
    return other *= rhs;
  }

  friend constexpr vecn operator/(const vecn& lhs, const vecn& rhs) noexcept {
    vecn other = lhs;
    return other /= rhs;
  }

  template<typename Other>
    requires(std::is_arithmetic_v<Other>)
  friend constexpr vecn operator*(const vecn& lhs, const Other& rhs) noexcept {
    vecn other = lhs;
    return other *= rhs;
  }

  template<typename Other>
    requires(std::is_arithmetic_v<Other>)
  friend constexpr vecn operator*(const Other& lhs, const vecn& rhs) noexcept {
    //!@NOTE commutative property may not hold for all `Type`
    return rhs * lhs;
  }

  template<typename Other>
    requires(std::is_arithmetic_v<Other>)
  friend constexpr vecn operator/(const vecn& lhs, const Other& rhs) noexcept {
    vecn other = lhs;
    return other /= rhs;
  }

  constexpr Type& operator[](const size_t index) noexcept {
    return values.at(index);
  }

  constexpr const Type& operator[](const size_t index) const noexcept {
    return values.at(index);
  }

  template<SwizTag Tag>
  constexpr auto operator()(flp::SwizTagType<Tag> tag_instance) noexcept {
    return [this]<size_t... Indices>(std::integer_sequence<size_t, Indices...>) {
      return Swizzle<vecn, Type, Indices...> { *this };
    }(get_swiz_indices(tag_instance));
  }

  template<SwizTag Tag>
  constexpr auto operator()(flp::SwizTagType<Tag> tag_instance) const noexcept {
    return [this]<size_t... Indices>(std::integer_sequence<size_t, Indices...>) {
      return Swizzle<const vecn, Type, Indices...> { *this };
    }(get_swiz_indices(tag_instance));
  }

  friend auto operator<=>(const vecn&, const vecn&) noexcept = default;

  Type* ptr() noexcept {
    return values.data();
  }

  const Type* ptr() const noexcept {
    return values.data();
  }

  template<typename Self>
  [[nodiscard]]
  constexpr decltype(auto) x(this Self&& self) {
    return std::forward<Self>(self).values.at(0);
  }

  template<typename Self>
  [[nodiscard]]
  constexpr decltype(auto) y(this Self&& self) {
    return std::forward<Self>(self).values.at(1);
  }

  template<typename Self>
  [[nodiscard]]
  constexpr decltype(auto) z(this Self&& self)
    requires(Count >= 3)
  {
    return std::forward<Self>(self).values.at(2);
  }

  template<typename Self>
  [[nodiscard]]
  constexpr decltype(auto) w(this Self&& self)
    requires(Count >= 4)
  {
    return std::forward<Self>(self).values.at(3);
  }

  std::array<Type, Count> values {};
};

} // namespace flp

template<typename Type, size_t Count>
struct std::formatter<flp::vecn<Type, Count>> {
  constexpr auto parse(std::format_parse_context& context) {
    auto iterator = context.begin();

    while (iterator != context.end() and *iterator != '}') {
      ++iterator;
    }

    // VERIFY(iterator == context.end() or *iterator == '}', "");

    return iterator;
  }

  constexpr auto format(const flp::vecn<Type, Count>& vec, std::format_context& context) const {
    auto iter = std::format_to(context.out(), "( ");

    [&vec, &iter]<size_t... Indices>(std::integer_sequence<size_t, Indices...>) {
      ((iter = std::format_to(iter, "{} ", vec[Indices])), ...);
    }(std::make_integer_sequence<size_t, Count>());

    return std::format_to(iter, ")");
  }
};

template<typename OStream, typename Type, size_t Count>
OStream& operator<<(OStream& ostream, const flp::vecn<Type, Count>& vec) {
  return ostream << std::format("{}", vec);
}
