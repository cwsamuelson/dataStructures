#pragma once

namespace flp::Colors {

struct RGBA {
  union {
    struct {
      uint8_t red;
      uint8_t green;
      uint8_t blue;
      uint8_t alpha;
    };

    uint32_t value;
  };
};

} // namespace flp
