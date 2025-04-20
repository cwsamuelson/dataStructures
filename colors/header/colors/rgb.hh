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
    uint32_t value;
  };
};

} // namespace flp

