#pragma once

#include <cstdint>

namespace flp::Colors {

template<typename Type = uint8_t>
struct RGBA {
  union {
    struct {
      Type red;
      Type green;
      Type blue;
      Type alpha;
    };

    struct {
      Type r;
      Type g;
      Type b;
      Type a;
    };

    uint32_t value;
    Type bytes[4];
  };
};

} // namespace flp::Colors
