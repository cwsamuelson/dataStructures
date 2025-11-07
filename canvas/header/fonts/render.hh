#pragma once

#include <cstddef>

namespace Fonts {

void render(auto& target, const auto& bitmap, const auto& value) {
  for (size_t x = 0; x < 8; x++) {
    for (size_t y = 0; y < 8; y++) {
      if (bitmap[x] & 1 << y) {
        target[y][x] = value;
      }
    }
  }
}

}
