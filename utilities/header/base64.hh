#pragma once

#include <array>
#include <ranges>
#include <string>

namespace flp::Base64 {

static constexpr const char* const default_dictionary =
  "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

[[nodiscard]]
constexpr
std::string encode(const std::string_view text, const char* const dictionary) noexcept {
  std::string encoding;

  for (const auto c : text | std::views::chunk(3)) {
    std::array<char, 3> chunk;

    for (auto&& [byte, value] : std::views::zip(chunk, c)) {
      byte = value;
    }

    for (size_t i = c.size(); i < 3; ++i) {
      chunk[i] = '\0';
    }

    const std::array<char, 4> indices {
      ((chunk[0] & 0b11111100) >> 2),
      ((chunk[0] & 0b00000011) << 4) | ((chunk[1] & 0b11110000) >> 4),
      ((chunk[1] & 0b00001111) << 2) | ((chunk[2] & 0b11000000) >> 6),
      ((chunk[2] & 0b00111111) << 0),
    };

    for (const auto index : indices) {
      encoding.push_back(dictionary[static_cast<size_t>(index)]);
    }
  }

  return encoding;
}

[[nodiscard]]
constexpr
std::string encode(const std::string_view text) noexcept {
  return encode(text, default_dictionary);
}

[[nodiscard]]
constexpr
std::string decode(const std::string_view encoding, const char* const dictionary) noexcept {
  return "";
}

[[nodiscard]]
constexpr
std::string decode(const std::string_view encoding) noexcept {
  return decode(encoding, default_dictionary);
}

}
