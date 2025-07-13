#pragma once

#include <cstdint>

namespace flp::Colors {

struct RGBA {
  union {
    struct {
      uint8_t red;
      uint8_t green;
      uint8_t blue;
      uint8_t alpha;
    };

    struct {
      uint8_t r;
      uint8_t g;
      uint8_t b;
      uint8_t a;
    };

    uint32_t value;
    uint8_t bytes[4];
  };
};

} // namespace flp::Colors
