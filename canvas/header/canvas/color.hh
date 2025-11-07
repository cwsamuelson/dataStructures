#pragma once

#include <compare>
#include <cstdint>

namespace flp {

struct ColorRGBA32 {
  union {
    struct {
      uint8_t r;
      uint8_t g;
      uint8_t b;
      uint8_t a;
    };

    struct {
      uint8_t red;
      uint8_t green;
      uint8_t blue;
      uint8_t alpha;
    };

    uint32_t value;
  };

  template<std::unsigned_integral UInt>
  constexpr
  ColorRGBA32(const UInt R, const UInt G, const UInt B, const UInt A)
    : red(R)
    , green(G)
    , blue(B)
    , alpha(A)
  {}

  // assume normalized values
  constexpr
  ColorRGBA32(const float R, const float G, const float B, const float A)
    : red(R * 255)
    , green(G * 255)
    , blue(B * 255)
    , alpha(A * 255)
  {}

  constexpr
  ColorRGBA32(const uint32_t V)
    : value(V)
  {}

  friend auto operator<=>(const ColorRGBA32& lhs, const ColorRGBA32& rhs) noexcept {
    return lhs.value <=> rhs.value;
  }

  friend bool operator==(const ColorRGBA32& lhs, const ColorRGBA32& rhs) noexcept {
    return lhs.value == rhs.value;
  }
};

}
