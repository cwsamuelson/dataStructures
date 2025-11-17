#pragma once

#include <array>
#include <bitset>
#include <cstdint>
#include <random>
#include <ranges>
#include <string>

namespace flp::UUID {

struct V4 {
  template<typename Source>
  static
  V4 generate(Source&& source) noexcept {
    std::uniform_int_distribution<uint64_t> distribution;
    const auto a = distribution(source());
    const auto b = distribution(source());
    return { a, b };
  }

  static
  // string_view is parsed as a formatted UUID string
  V4 parse(const std::string_view text) {
    // f50a34b2-e522-4394-82cc-e9e36a8f6681
    // UUID with '-'s is 36 characters long
    // f50a34b2e522439482cce9e36a8f6681
    // UUID without '-'s is 32 characters long
    // VERIFY(text.size() == 36 or text.size() == 32, "");

    V4 uuid;

    if (text.size() == 36) {
      // auto blocks = text | std::views::split("-");
      // VERIFY(blocks.size() == 5, "");
    } else if (text.size() == 32) {
      // 4 'bytes',  8 hex characters
      // 2 'bytes',  4 hex characters
      // 2 'bytes',  4 hex characters
      // 2 'bytes',  4 hex characters
      // 6 'bytes', 12 hex characters
    }

    return uuid;
  }

  static constexpr std::bitset<4> version = 0b0100;
  // static constexpr V4 null{};

  V4() = default;

  V4(uint32_t, uint16_t, uint16_t, uint16_t, uint64_t);

  V4(const std::array<std::byte, 4>&,
     const std::array<std::byte, 2>&,
     const std::array<std::byte, 2>&,
     const std::array<std::byte, 2>&,
     const std::array<std::byte, 6>&);

  V4(const std::array<std::byte, 16>&);

  V4(const std::array<uint64_t, 2>&);

  V4(uint64_t, uint64_t);
  // V4(uint128_t);
  // string_view is used as a byte source
  V4(std::string_view);
};

}
