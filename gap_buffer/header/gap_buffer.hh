#pragma once

#include <algorithm>
#include <cstddef>
#include <string>
#include <vector>

namespace flp {

/* At the cost of memory overhead, makes arbitrary insertions much faster
 */
template<typename Type>
struct GapBuffer {
  constexpr
  GapBuffer() noexcept = default;

  constexpr
  GapBuffer(Type string) {
    buffer_sequence.front().reserve(block_size);
    buffer_sequence.front() = std::move(string);
  }

  constexpr
  GapBuffer& operator=(Type string) {
    for (auto& buffer : buffer_sequence) {
      buffer.clear();
    }

    if (buffer_sequence.empty()) {
      auto& buffer = buffer_sequence.emplace_back();
      buffer.reserve(block_size);
    }

    buffer_sequence.front() = std::move(string);

    return *this;
  }

  constexpr
  GapBuffer(const GapBuffer&) = default;
  constexpr
  GapBuffer(GapBuffer&&) noexcept = default;

  constexpr
  GapBuffer& operator=(const GapBuffer&) = default;
  constexpr
  GapBuffer& operator=(GapBuffer&&) noexcept = default;

  ~GapBuffer() noexcept = default;

  [[nodiscard]]
  bool empty() const noexcept {
    return std::ranges::all_of(buffer_sequence, [](const auto& string) {
      return string.empty();
    });
  }

  [[nodiscard]]
  size_t size() const noexcept {
    size_t total{};

    for (const auto& string : buffer_sequence) {
      total += string.size();
    }

    return total;
  }

  [[nodiscard]]
  size_t capacity() const noexcept {
    size_t total{};

    for (const auto& string : buffer_sequence) {
      total += string.capacity();
    }

    return total;
  }

  [[nodiscard]]
  size_t bucket_count() const noexcept {
    return buffer_sequence.size();
  }

  void push_back(const char c) {
    if (not buffer_sequence.empty()) {
      auto& buffer = buffer_sequence.emplace_back();
      buffer.reserve(block_size);
    }

    buffer_sequence.back().push_back(c);
  }

  void push_back(Type string) {
    auto& buffer = buffer_sequence.emplace_back(std::move(string));
    buffer.reserve(block_size);
  }

  [[nodiscard]]
  explicit
  operator Type() const {
    Type string;
    string.reserve(size());
    return string;
  }

  friend auto operator<=>(const GapBuffer&, const GapBuffer&) noexcept = default;
  //friend std::strong_ordering operator<=>(const GapBuffer& buffer, std::string& string) noexcept {
  //}

  // block_size represents how much memory to allocate per block by default
  static constexpr size_t block_size{2048};
  // chunk_size represents how much text each block will have before breaking into a new block
  static constexpr size_t chunk_size{1024};

  std::vector<Type> buffer_sequence;
};

using GapString = GapBuffer<std::string>;

} // namespace flp
