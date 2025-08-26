#pragma once

#include <core/maybe_const.hh>

#include <algorithm>
#include <cstddef>
#include <string>
#include <vector>

namespace flp {

// When I wrote this, I thought I was writing the `GapBuffer`, but soon realized
// I was confused.  The result is something approximating `Hive` for strings.
// It's incomplete, but may be suitable for text editing.

/* At the cost of memory overhead, makes arbitrary insertions much faster
 */
template<typename Type>
struct ChunkedArray {
  template<bool IsConst>
  struct Iterator;

  using iterator = Iterator<false>;
  using const_iterator = Iterator<true>;

  template<bool IsConst>
  struct Iterator {
    using value_type = Type::value_type;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::bidirectional_iterator_tag;
    using pointer = MaybeConst<value_type, IsConst>*;
    using reference = MaybeConst<value_type, IsConst>&;

    using Container = MaybeConst<ChunkedArray, IsConst>;
    using BlockIterator = decltype(std::declval<std::remove_reference_t<Container>>().buffer_sequence.begin());

    Container* buffer = nullptr;
    BlockIterator block_it;
    size_t index{};

    Iterator(Container* container, BlockIterator iter, size_t idx)
      : buffer(container)
      , block_it(iter)
      , index(idx)
    {}

    Iterator() noexcept = default;
    Iterator(const Iterator&) = default;
    Iterator(Iterator&&) noexcept = default;
    Iterator& operator=(const Iterator&) = default;
    Iterator& operator=(Iterator&&) noexcept = default;
    ~Iterator() noexcept = default;

    Iterator(const Iterator<false>& other)
      requires (IsConst) // otherwise it's a duplicate definition
      : buffer(other.buffer)
      , block_it(other.block_it)
      , index(other.index)
    {}

    Iterator(Iterator<false>&& other) noexcept
      requires (IsConst) // otherwise it's a duplicate definition
      : buffer(other.buffer)
      , block_it(std::move(other.block_it))
      , index(other.index)
    {}

    Iterator& operator=(const Iterator<false>& other)
      requires (IsConst) {
      buffer = other.buffer;
      block_it = other.block_it;
      index = other.index;
      return *this;
    }

    Iterator& operator=(Iterator<false>&& other) noexcept
      requires (IsConst) {
      buffer = other.buffer;
      block_it = std::move(other.block_it);
      index = other.index;
      return *this;
    }

    friend bool operator==(const Iterator& lhs, const Iterator& rhs) noexcept = default;
    friend auto operator<=>(const Iterator& lhs, const Iterator& rhs) noexcept = default;

    reference operator*(this auto&& self) noexcept {
      return self.block_it->at(self.index);
    }

    pointer operator->(this auto&& self) noexcept {
      return &self.block_it->at(self.index);
    }

    Iterator& operator++() noexcept {
      if (block_it == buffer->buffer_sequence.end()) {
        return *this;
      }

      ++index;

      if (index == block_it->size()) {
        ++block_it;
        index = 0;
      }

      return *this;
    }

    Iterator operator++(int) noexcept {
      Iterator copy = *this;
      ++(*this);
      return copy;
    }

    Iterator& operator--() noexcept {
      if (index == 0) {
        --block_it;
        return *this;
      }

      --index;

      return *this;
    }

    Iterator operator--(int) noexcept {
      Iterator copy = *this;
      --(*this);
      return copy;
    }
  };

  constexpr
  ChunkedArray() noexcept = default;

  constexpr
  ChunkedArray(Type string)
    : buffer_sequence(1, std::move(string)) {
    buffer_sequence.front().reserve(block_size);
  }

  constexpr
  ChunkedArray& operator=(Type string) {
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
  ChunkedArray(const ChunkedArray&) = default;
  constexpr
  ChunkedArray(ChunkedArray&&) noexcept = default;

  constexpr
  ChunkedArray& operator=(const ChunkedArray&) = default;
  constexpr
  ChunkedArray& operator=(ChunkedArray&&) noexcept = default;

  ~ChunkedArray() noexcept = default;

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

  [[nodiscard]]
  decltype(auto) operator[](this auto&& self, size_t index) {
    auto buf_iter = self.buffer_sequence.begin();
    while (index > buf_iter->size()) {
      index -= buf_iter->size();
      ++buf_iter;
    }

    return (*buf_iter)[index];
  }

  decltype(auto) front(this auto&& self) {
    return self.buffer_sequence.front().front();
  }

  decltype(auto) back(this auto&& self) {
    return self.buffer_sequence.back().back();
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
    //buffer.reserve(block_size);// ?
  }

  ChunkedArray& operator+=(const ChunkedArray& other) {
    for (auto& buffer : other.buffer_sequence) {
      buffer_sequence.emplace_back(buffer);
    }

    return *this;
  }

  ChunkedArray& operator+=(ChunkedArray&& other) {
    for (auto& buffer : other.buffer_sequence) {
      buffer_sequence.emplace_back(std::move(buffer));
    }
    other.buffer_sequence.clear();

    return *this;
  }

  ChunkedArray operator+(const ChunkedArray& other) {
    return ChunkedArray(*this) += other;
  }

  ChunkedArray operator+(ChunkedArray&& other) {
    return ChunkedArray(*this) += std::move(other);
  }

  ChunkedArray& operator+=(const std::string& string) {
    buffer_sequence.emplace_back(string);
    return *this;
  }

  ChunkedArray& operator+=(std::string&& string) {
    buffer_sequence.emplace_back(std::move(string));
    return *this;
  }

  ChunkedArray operator+(const std::string& string) {
    return ChunkedArray(*this) += string;
  }

  ChunkedArray operator+(std::string&& string) {
    return ChunkedArray(*this) += std::move(string);
  }

  [[nodiscard]]
  explicit
  operator Type() const {
    Type string;
    string.reserve(size());
    return string;
  }

  friend auto operator<=>(const ChunkedArray& lhs, const ChunkedArray& rhs) noexcept {
    auto lhs_iter = lhs.begin();
    auto rhs_iter = rhs.begin();

    while (lhs_iter != lhs.end() and rhs_iter != rhs.end()) {
      if (*lhs_iter != *rhs_iter) {
        return *lhs_iter <=> *rhs_iter;
      }
      ++lhs_iter;
      ++rhs_iter;
    }

    if (lhs_iter == lhs.end()) {
      return std::strong_ordering::less;
    }

    if (rhs_iter == rhs.end()) {
      return std::strong_ordering::greater;
    }

    return std::strong_ordering::equal;
  }

  friend
  std::strong_ordering operator<=>(
    const ChunkedArray& buffer,
    const char* string
  ) noexcept {
    return buffer <=> std::string_view(string);
  }

  friend
  std::strong_ordering operator<=>(
    const ChunkedArray& buffer,
    const std::string_view& string
  ) noexcept {
    auto buf_iter = buffer.begin();
    auto str_iter = string.begin();

    while (buf_iter != buffer.end() and str_iter != string.end()) {
      if (*buf_iter != *str_iter) {
        return *buf_iter <=> *str_iter;
      }
      ++buf_iter;
      ++str_iter;
    }

    if (buf_iter == buffer.end()) {
      return std::strong_ordering::less;
    }

    if (str_iter == string.end()) {
      return std::strong_ordering::greater;
    }

    return std::strong_ordering::equal;
  }

  [[nodiscard]]
  friend
  bool operator==(const ChunkedArray& buffer, const std::string_view& string) {
    auto buf_iter = buffer.begin();
    auto str_iter = string.begin();

    while (buf_iter != buffer.end() and str_iter != string.end()) {
      if (*buf_iter != *str_iter) {
        return false;
      }
      ++buf_iter;
      ++str_iter;
    }

    return true;
  }

  template<typename Self>
  auto begin(this Self&& self) noexcept {
    return Iterator<std::is_const_v<std::remove_reference_t<Self>>>(&self, self.buffer_sequence.begin(), 0);
  }

  template<typename Self>
  auto end(this Self&& self) noexcept {
    return Iterator<std::is_const_v<std::remove_reference_t<Self>>>(&self, self.buffer_sequence.end(), 0);
  }

  const_iterator cbegin() const;
  const_iterator cend() const;

  // block_size represents how much memory to allocate per block by default
  static constexpr size_t block_size{2048};
  // chunk_size represents how much text each block will have before breaking into a new block
  static constexpr size_t chunk_size{1024};

  std::vector<Type> buffer_sequence;
};

using ChunkedString = ChunkedArray<std::string>;

} // namespace flp
