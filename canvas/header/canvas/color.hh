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

  constexpr
  ColorRGBA32(const uint8_t R, const uint8_t G, const uint8_t B, const uint8_t A)
    : red(R)
    , green(G)
    , blue(B)
    , alpha(A)
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
