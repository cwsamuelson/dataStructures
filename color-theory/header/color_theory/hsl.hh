#pragma once

#include <cstdint>

namespace flp::Colors {

template<typename Type = uint8_t>
struct HSL {
  union {
    struct {
      Type hue;
      Type saturation;
      Type luminance;
    };

    struct {
      Type h;
      Type s;
      Type l;
    };

    uint32_t value;
    uint8_t bytes[3];
  };
};

} // namespace flp::Colors
