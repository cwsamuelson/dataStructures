#pragma once

#include <array>
#include <ranges>
#include <string>

namespace flp::Base64 {

static constexpr const char* const default_dictionary =
  "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

// This table can function as a guide to how encoding/decoding works
// message  |       'M'     |      'a'      |      'n'      |
// value    |       77      |      97       |      110      |
// bits     |0|1|0|0|1|1|0|1|0|1|1|0|0|0|0|1|0|1|1|0|1|1|1|0|
// value    |     19    |     22    |      5    |     46    |
// encoding |      T    |      W    |      F    |      u    |
// byte     |     84    |     87    |     70    |    117    |
//
// As you may infer from the table, a messages is ingested in 3 byte chunks.
// Each 6 bits of that chunk are then parsed as their own number, and used as an
// index into the dictionary to obtain the encoded character.
//
// Similarly, when decoding, the encoded message is ingested in 4 byte chunks.
// For each byte, the character is found in the dictionary, and its index is
// used as the 'value' to reconstruct the message.

// encode one chunk
[[nodiscard]]
constexpr
std::array<char, 4> encode(const std::array<char, 3>& chunk, const char* const dictionary) noexcept {
  std::array<char, 4> encoding;

  const std::array<char, 4> indices {
    ((chunk[0] & 0b11111100) >> 2),
    ((chunk[0] & 0b00000011) << 4) | ((chunk[1] & 0b11110000) >> 4),
    ((chunk[1] & 0b00001111) << 2) | ((chunk[2] & 0b11000000) >> 6),
    ((chunk[2] & 0b00111111) << 0),
  };

  for (auto&& [e, index] : std::views::zip(encoding, indices)) {
    e = dictionary[static_cast<size_t>(index)];
  }

  return encoding;
}

[[nodiscard]]
constexpr
std::string encode(const std::string_view text, const char* const dictionary) noexcept {
  std::string encoding;

  for (const auto c : text | std::views::chunk(3)) {
    // std::chunk doesn't pad out, and we want to work with with same-sized chunks
    std::array<char, 3> chunk;

    for (auto&& [byte, value] : std::views::zip(chunk, c)) {
      byte = value;
    }

    for (size_t i = c.size(); i < 3; ++i) {
      chunk[i] = '\0';
    }

    encoding.append_range(encode(chunk, dictionary));
  }

  if (text.size() % 3 == 1) {
    encoding[encoding.size() - 1] = '=';
    encoding[encoding.size() - 2] = '=';
  } else if (text.size() % 3 == 2) {
    encoding[encoding.size() - 1] = '=';
  }

  return encoding;
}

[[nodiscard]]
constexpr
std::string encode(const std::string_view text) noexcept {
  return encode(text, default_dictionary);
}

// decode one chunk
[[nodiscard]]
constexpr
std::array<uint8_t, 3> decode(const std::array<uint8_t, 4>& chunk, const std::string_view dictionary) noexcept {
  const auto offsets =
      chunk
    | std::views::transform([&] (const auto b) {
      return std::find(dictionary.begin(), dictionary.end(), b) - dictionary.begin();
    });

  return {
    ((offsets[0] & 0b111111) << 2) | ((offsets[1] & 0b110000) >> 4),
    ((offsets[1] & 0b001111) << 4) | ((offsets[2] & 0b111100) >> 2),
    ((offsets[2] & 0b000011) << 6) | ((offsets[3] & 0b111111) >> 0),
  };
}

[[nodiscard]]
constexpr
std::string decode(const std::string_view encoding, const char* const dictionary) noexcept {
  // VERIFY(encoding.size() % 4 == 0, "Invalid base 64 encoded message.  Expected the message to come in 4 byte chunks.");

  std::string message;

  for (const auto c : encoding | std::views::chunk(4)) {
    std::array<uint8_t, 4> chunk;

    for (auto&& [byte, value] :
      std::views::zip(chunk,
          c
        | std::views::transform([](const auto x) -> uint8_t {
          return x == '=' ? 0 : x;
        })
      )
    ) {
      byte = value;
    }

    message.append_range(decode(chunk, dictionary));
  }

  if (encoding[encoding.size() - 2] == '=') {
    message.pop_back();
    message.pop_back();
  } else if (encoding[encoding.size() - 1] == '=') {
    message.pop_back();
  }

  return message;
}

[[nodiscard]]
constexpr
std::string decode(const std::string_view encoding) noexcept {
  return decode(encoding, default_dictionary);
}

}
