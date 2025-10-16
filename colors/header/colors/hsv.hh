#pragma once

namespace flp::Colors {

template<typename Type = uint8_t>
struct HSV {
  union {
    struct {
      Type hue;
      Type saturation;
      Type value;
    };

    struct {
      Type h;
      Type s;
      Type v;
    };

    //uint32_t value;
    Type bytes[3];
  };
};

} // namespace flp::Colors
