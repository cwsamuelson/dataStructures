#pragma once

#include <cstdint>

namespace flp::Colors {

struct RGB {
  union {
    struct {
      uint8_t red;
      uint8_t green;
      uint8_t blue;
    };

    struct {
      uint8_t r;
      uint8_t g;
      uint8_t b;
    };

    uint32_t value;

    uint8_t bytes[3];
  };
};

} // namespace flp
