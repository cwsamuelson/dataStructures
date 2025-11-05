#pragma once

#include <array>
#include <bitset>
#include <cstdint>
#include <string>

namespace flp::UUID {

struct V4 {
  static constexpr std::bitset<4> version = 0b0100;

  V4();
  V4(uint32_t, uint16_t, uint16_t, uint64_t);
  V4(std::array<std::byte, 4>, std::array<std::byte, 2>, std::array<std::byte, 2>, std::array<std::byte, 8>);
  V4(std::array<std::byte, 16>);
  V4(std::array<uint64_t, 2>);
  V4(uint64_t, uint64_t);
  V4(std::string_view);
};

}
