#pragma once

namespace flp::Colors {

// could template for different representations
//template<typename Type>
struct HSL {
  union {
    struct {
      uint8_t hue;
      uint8_t saturation;
      uint8_t luminance;
    };

    struct {
      uint8_t h;
      uint8_t s;
      uint8_t l;
    };

    uint32_t value;
    uint8_t bytes[3];
  };
};

} // namespace flp::Colors
