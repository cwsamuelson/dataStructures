#pragma once

#include <array>
#include <bitset>
#include <cstdint>
#include <random>
#include <string>

namespace flp::UUID {

struct V4 {
  template<typename Source>
  static
  V4 generate(Source&& source) {
    std::uniform_int_distribution<uint64_t> distribution;
    const auto a = distribution(source());
    const auto b = distribution(source());
    return { a, b };
  }
  static
  // string_view is parsed as a formatted UUID string
  V4 parse(std::string_view);

  static constexpr std::bitset<4> version = 0b0100;

  V4() = default;;
  V4(uint32_t, uint16_t, uint16_t, uint64_t);
  V4(std::array<std::byte, 4>, std::array<std::byte, 2>, std::array<std::byte, 2>, std::array<std::byte, 8>);
  V4(std::array<std::byte, 16>);
  V4(std::array<uint64_t, 2>);
  V4(uint64_t, uint64_t);
  // string_view is used as a byte source
  V4(std::string_view);
};

}
