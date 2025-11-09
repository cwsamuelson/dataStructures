#pragma once

#include <core/traits/integral.hh>

namespace flp {

template<typename Type>
struct Position2 {
  Type x;
  Type y;

  friend
  auto operator<=>(const Position2&, const Position2&) noexcept = default;
};

template<typename Type>
struct Size2 {
  Type width;
  Type height;
};

template<typename Type>
struct vec2 {
  Type x;
  Type y;
};

// math with constant
template<typename Type>
Position2<Type> operator+(const Position2<Type>& position, const Type& constant) noexcept {
  return { position.x + constant, position.y + constant };
}

template<typename Type>
Position2<MakeSigned<Type>> operator-(const Position2<Type>& position, const Type& constant) noexcept {
  return { position.x - constant, position.y - constant };
}

template<typename Type>
Position2<Type> operator*(const Position2<Type>& position, const Type& constant) noexcept {
  return { position.x * constant, position.y * constant };
}

template<typename Type>
Position2<Type> operator/(const Position2<Type>& position, const Type& constant) noexcept {
  return { position.x / constant, position.y / constant };
}

// math with self

template<typename Type>
vec2<Type> operator+(const Position2<Type>& start, const Position2<Type>& stop) noexcept {
  return { start.x + stop.x, start.y + stop.y };
}

template<typename Type>
vec2<MakeSigned<Type>> operator-(const Position2<Type>& start, const Position2<Type>& stop) noexcept {
  return { start.x - stop.x, start.y - stop.y };
}

// math with vec

template<typename Type>
Position2<Type> operator+(const Position2<Type>& position, const vec2<Type>& offset) noexcept {
  return { position.x + offset.x, position.y + offset.y };
}

template<typename Type>
Position2<MakeSigned<Type>> operator-(const Position2<Type>& position, const vec2<Type>& offset) noexcept {
  return { position.x - offset.x, position.y - offset.y };
}

// math with size
template<typename Type>
Position2<Type> operator+(const Position2<Type>& position, const Size2<Type>& size) noexcept {
  return { position.x + size.width, position.y + size.height };
}

template<typename Type>
Position2<MakeSigned<Type>> operator-(const Position2<Type>& position, const Size2<Type>& size) noexcept {
  return { position.x - size.width, position.y - size.height };
}

template<typename Type>
Size2<Type> operator+(const Size2<Type>& size, const Size2<Type>& delta) noexcept {
  return { size.width + delta.width, size.height + delta.height };
}

template<typename Type>
Size2<Type> operator-(const Size2<Type>& size, const Size2<Type>& delta) noexcept {
  return { size.width - delta.width, size.height - delta.height };
}

}
