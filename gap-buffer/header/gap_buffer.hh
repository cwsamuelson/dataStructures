#pragma once

#include <core/maybe_const.hh>

#include <cstddef>
#include <string>

namespace flp {

template<typename Type>
struct GapBuffer {
  using value_type = Type::value_type;
  using buffer_type = Type;

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

    using Container = MaybeConst<GapBuffer, IsConst>;

    Container* buffer = nullptr;
    size_t index{};

    Iterator(Container* container, size_t idx)
      : buffer(container)
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
      , index(other.index)
    {}

    Iterator(Iterator<false>&& other) noexcept
      requires (IsConst) // otherwise it's a duplicate definition
      : buffer(other.buffer)
      , index(other.index)
    {}

    Iterator& operator=(const Iterator<false>& other)
      requires (IsConst) {
      buffer = other.buffer;
      index = other.index;
      return *this;
    }

    Iterator& operator=(Iterator<false>&& other) noexcept
      requires (IsConst) {
      buffer = other.buffer;
      index = other.index;
      return *this;
    }

    friend bool operator==(const Iterator& lhs, const Iterator& rhs) noexcept = default;
    friend auto operator<=>(const Iterator& lhs, const Iterator& rhs) noexcept = default;

    reference operator*(this auto&& self) noexcept {
      return self.buffer->data.at(self.index);
    }

    pointer operator->(this auto&& self) noexcept {
      return &self.buffer->data.at(self.index);
    }

    Iterator& operator++() noexcept {
      ++index;

      if (index == buffer->gap.start) {
        index = buffer->gap.end;
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
  GapBuffer() noexcept = default;

  constexpr
  GapBuffer(Type string)
    : data(std::move(string))
  {}

  constexpr
  GapBuffer& operator=(Type string) {
    data = std::move(string);
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
  constexpr
  explicit
  operator Type(this auto&& self) noexcept {
    const auto s = self.size();

    std::string_view p1(self.data(), self.gap.start);
    std::string_view p2(self.data() + self.gap.end, s - self.gap.end);

    Type value;
    value.reserve(s);

    value.append_range(p1);
    value.append_range(p2);

    return value;
  }

  [[nodiscard]]
  size_t cursor() const noexcept {
    return gap.start;
  }

  void cursor(const size_t index) noexcept {
    const signed long long offset = gap.start - index;
    const size_t size = gap.end - gap.start;
    // `ABCDEFGHIJKLMNOPQRSTUVWXYZ`

    // Initial
    // `ABCDEFGHIJKL      MNOPQRSTUVWXYZ`
    // `            ^    ^              `

    // Target
    // `ABCDEFGHIJKL  IJKLMNOPQRSTUVWXYZ`
    // `        ^    ^                  `
    // Offset: -4
    // Destination: index
    // Size: |Offset|

    // Target
    // `ABCDEFGHIJKLMNOP      QRSTUVWXYZ`
    // `                ^    ^          `
    // Offset: 4

    std::copy(data.data() + index, data.data() + index + size, data.data() + gap.end + offset);

    gap.start += offset;
    gap.end += offset;
  }

  [[nodiscard]]
  constexpr
  size_t size() const noexcept {
    return data.size() - (gap.end - gap.start);
  }

  [[nodiscard]]
  constexpr
  size_t capacity() const noexcept {
    return data.capacity();
  }

  [[nodiscard]]
  constexpr
  bool empty() const noexcept {
    return size() == 0;
  }

  [[nodiscard]]
  constexpr
  decltype(auto) operator[](this auto&& self, const size_t index) {
    if (index > self.gap.start) {
      return self.data[self.gap.end + (index - self.gap.start)];
    }

    return self.data[index];
  }

  [[nodiscard]]
  constexpr
  decltype(auto) front(this auto&& self) {
    return self.data.front();
  }

  [[nodiscard]]
  constexpr
  decltype(auto) back(this auto&& self) {
    return self.data.back();
  }

  void clear() noexcept {
    data.clear();
  }

  [[nodiscard]]
  constexpr
  friend
  auto operator<=>(const GapBuffer& lhs, const GapBuffer& rhs) noexcept {
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

  [[nodiscard]]
  constexpr
  friend
  auto operator<=>(const GapBuffer& buffer, const std::string_view& string) noexcept {
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
  constexpr
  friend
  bool operator==(const GapBuffer& buffer, const std::string_view& string) noexcept {
    auto buf_iter = buffer.begin();
    auto str_iter = string.begin();

    while (buf_iter != buffer.end() and str_iter != string.end()) {
      if (*buf_iter != *str_iter) {
        return false;
      }

      ++buf_iter;
      ++str_iter;
    }

    return buf_iter == buffer.end() and str_iter == string.end();
  }

  template<typename Self>
  auto begin(this Self&& self) noexcept {
    return Iterator<std::is_const_v<std::remove_reference_t<Self>>>(&self, 0);
  }

  template<typename Self>
  auto end(this Self&& self) noexcept {
    return Iterator<std::is_const_v<std::remove_reference_t<Self>>>(&self, self.data.size());
  }

  const_iterator cbegin() const;
  const_iterator cend() const;

  struct Gap {
    size_t start{};
    size_t end{};
  };

  Type data;
  Gap gap;
};

using GapString = GapBuffer<std::string>;

} // namespace flp
