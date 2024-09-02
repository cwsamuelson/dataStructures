#pragma once

#include <concepts>
#include <utility>

namespace flp {

// the lambda trick ensures every instantiation is unique
// this eliminates the need for special tag types
// however, their use is still possible
template<typename Type, typename /*Tag*/>
struct TaggedType {
  using value_type = Type;

  Type value {};

  constexpr TaggedType() noexcept = default;

  constexpr TaggedType(const Type val) noexcept
    : value(val) {}

  constexpr TaggedType(const TaggedType&) noexcept = default;
  constexpr TaggedType(TaggedType&&) noexcept      = default;

  constexpr TaggedType& operator=(const TaggedType&) noexcept = default;
  constexpr TaggedType& operator=(TaggedType&&) noexcept      = default;

  constexpr ~TaggedType() = default;

  constexpr friend auto operator<=>(const TaggedType&, const TaggedType&) noexcept = default;

  /*constexpr friend auto operator<=>(const TaggedType& self, const std::integral auto other) noexcept
    requires std::integral<Type>
  {
    return static_cast<Type>(self) <=> other;
  }*/

  explicit constexpr operator Type() const noexcept {
    return value;
  }

  constexpr TaggedType& operator=(Type val) noexcept {
    value = std::move(val);
    return *this;
  }

  friend constexpr auto operator+(const TaggedType& lhs, const TaggedType& rhs) noexcept {
    return Type(lhs) + Type(rhs);
  }
  friend constexpr auto operator-(const TaggedType& lhs, const TaggedType& rhs) noexcept {
    return Type(lhs) - Type(rhs);
  }
  friend constexpr auto operator*(const TaggedType& lhs, const TaggedType& rhs) noexcept {
    return Type(lhs) * Type(rhs);
  }
  friend constexpr auto operator/(const TaggedType& lhs, const TaggedType& rhs) noexcept {
    return Type(lhs) / Type(rhs);
  }
};

} // namespace flp
