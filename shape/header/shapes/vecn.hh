#pragma once

#include <core/concepts.hh>
#include "shapes/swizzle.hh"

#include <array>
#include <concepts>
#include <cstddef>
#include <format>
#include <utility>

#include <print>

namespace flp {

template<typename Type, size_t Count>
struct vecn {
  constexpr
  vecn() noexcept
    : values{}
  {}

  template<std::same_as<Type> ...T>
  explicit
  constexpr
  vecn(const T& ...Values) noexcept
    : values{ Values... }
  {}

  constexpr
  friend
  vecn operator-(const vecn& vec) noexcept {
    auto negate = []<size_t ...Indices>(const vecn& vec, std::integer_sequence<size_t, Indices...>) noexcept {
      return vecn{ -vec.values[Indices]... };
    };

    return negate(vec, std::make_integer_sequence<size_t, Count>());
  }

  constexpr
  vecn& operator+=(const vecn& other) noexcept {
    [this]<size_t ...Indices>(const vecn& vec, std::integer_sequence<size_t, Indices...>) noexcept {
      ((values[Indices] += vec.values[Indices]), ...);
    }(other, std::make_integer_sequence<size_t, Count>());

    return *this;
  }

  constexpr
  vecn& operator-=(const vecn& other) noexcept {
    [this]<size_t ...Indices>(const vecn& vec, std::integer_sequence<size_t, Indices...>) noexcept {
      ((values[Indices] -= vec.values[Indices]), ...);
    }(other, std::make_integer_sequence<size_t, Count>());

    return *this;
  }

  constexpr
  vecn& operator*=(const vecn& other) noexcept {
    [this]<size_t ...Indices>(const vecn& vec, std::integer_sequence<size_t, Indices...>) noexcept {
      ((std::print("{} ", Indices)), ...);
      std::println("{}", values);
      std::println("{}", vec.values);
      ((values[Indices] *= vec.values[Indices]), ...);
    }(other, std::make_integer_sequence<size_t, Count>());

    return *this;
  }

  constexpr
  vecn& operator/=(const vecn& other) noexcept {
    [this]<size_t ...Indices>(const vecn& vec, std::integer_sequence<size_t, Indices...>) noexcept {
      ((values[Indices] /= vec.values[Indices]), ...);
    }(other, std::make_integer_sequence<size_t, Count>());

    return *this;
  }

  template<typename Other>
    requires (std::is_arithmetic_v<Other>)
  constexpr
  friend
  vecn& operator*=(vecn& vec, const Other& value) noexcept {
    [&vec]<size_t ...Indices>(const auto& value, std::integer_sequence<size_t, Indices...>) noexcept {
      ((vec.values[Indices] *= value), ...);
    }(value, std::make_integer_sequence<size_t, Count>());

    return vec;
  }

  template<typename Other>
    requires (std::is_arithmetic_v<Other>)
  constexpr
  friend
  vecn& operator/=(const vecn& vec, const Other& value) noexcept {
    [&vec]<size_t ...Indices>(const auto& value, std::integer_sequence<size_t, Indices...>) noexcept {
      ((vec.values[Indices] /= value), ...);
    }(value, std::make_integer_sequence<size_t, Count>());

    return vec;
  }

  friend
  constexpr
  vecn operator+(const vecn& lhs, const vecn& rhs) noexcept {
    vecn other = lhs;
    return other += rhs;
  }

  friend
  constexpr
  vecn operator-(const vecn& lhs, const vecn& rhs) noexcept {
    vecn other = lhs;
    return other -= rhs;
  }

  friend
  constexpr
  vecn operator*(const vecn& lhs, const vecn& rhs) noexcept {
    vecn other = lhs;
    return other *= rhs;
  }

  friend
  constexpr
  vecn operator/(const vecn& lhs, const vecn& rhs) noexcept {
    vecn other = lhs;
    return other /= rhs;
  }

  template<typename Other>
    requires (std::is_arithmetic_v<Other>)
  friend
  constexpr
  vecn operator*(const vecn& lhs, const Other& rhs) noexcept {
    vecn other = lhs;
    return other *= rhs;
  }

  template<typename Other>
    requires (std::is_arithmetic_v<Other>)
  friend
  constexpr
  vecn operator*(const Other& lhs, const vecn& rhs) noexcept {
    // commutative property
    return rhs * lhs;
  }

  template<typename Other>
    requires (std::is_arithmetic_v<Other>)
  friend
  constexpr
  vecn operator/(const vecn& lhs, const Other& rhs) noexcept {
    vecn other = lhs;
    return other /= rhs;
  }

  friend auto operator<=>(const vecn&, const vecn&) noexcept = default;

  Type* ptr() noexcept {
    return values.data();
  }

  const Type* ptr() const noexcept {
    return values.data();
  }

  constexpr
  Type& operator[](const size_t index) noexcept {
    return values.at(index);
  }

  constexpr
  const Type& operator[](const size_t index) const noexcept {
    return values.at(index);
  }

  std::array<Type, Count> values{};
};

}

template<typename Type, size_t Count>
struct std::formatter<flp::vecn<Type, Count>> {
  constexpr
  auto parse(std::format_parse_context& context) {
    auto iterator = context.begin();

    while (iterator != context.end() and *iterator != '}') {
      ++iterator;
    }

    //VERIFY(iterator == context.end() or *iterator == '}', "");

    return iterator;
  }

  constexpr
  auto format(const flp::vecn<Type, Count>& vec, std::format_context& context) const {
    auto iter = std::format_to(context.out(), "( ");

    [&vec, &iter]<size_t ...Indices>(std::integer_sequence<size_t, Indices...>){
      ((iter = std::format_to(iter, "{} ", vec[Indices])), ...);
    }(std::make_integer_sequence<size_t, Count>());

    return std::format_to(iter, ")");
  }
};

template<typename OStream, typename Type, size_t Count>
OStream& operator<<(OStream& ostream, const flp::vecn<Type, Count>& vec) {
  return ostream << std::format("{}", vec);
}
