#pragma once

#include <cstdint>

namespace flp::Colors {

template<typename Type = uint8_t>
struct RGB {
  union {
    struct {
      Type red;
      Type green;
      Type blue;
    };

    struct {
      Type r;
      Type g;
      Type b;
    };

    uint32_t value;

    Type bytes[3];
  };
};

} // namespace flp
