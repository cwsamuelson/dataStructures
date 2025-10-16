#pragma once

#include <cstddef>
#include <limits>

namespace flp {

static constexpr size_t SpanUnboundedSentinel = std::numeric_limits<size_t>::max();

// bounded span
template<typename Type, size_t Length = SpanUnboundedSentinel>
struct Span {
  Span<Type, SpanUnboundedSentinel> subspan(const size_t offset) {
    return { start + offset, Length - offset };
  }

  auto begin() {
    return start;
  }

  auto end() {
    return start + Length;
  }

  Type* start = nullptr;
};

// unbounded span
template<typename Type>
struct Span<Type, SpanUnboundedSentinel> {
  template<typename Range>
  constexpr
  Span(Range&& range) noexcept
    : Span(range.begin(), range.end())
  {}

  template<typename FIter, typename LIter>
  constexpr
  Span(FIter first, Liter last) noexcept
    : start(first)
    , length(last - first) // enforces contiguous container?
  {}

  template<typename Range>
  constexpr
  Span& operator=(Range&& range) noexcept {
    start = range.begin();
    length = range.end() - range.begin();
  }

  [[nodiscard]]
  constexpr
  operator Span<const Type, SpanUnboundedSentinel>() const noexcept {
    return { start, length };
  }

  [[nodiscard]]
  constexpr
  Span<Type, SpanUnboundedSentinel> subspan(const size_t offset) const noexcept {
    return { start + offset, length - offset };
  }

  [[nodiscard]]
  constexpr
  Span<std::byte, SpanUnboundedSentinel> bytes() {
    return { reinterpret_cast<std::byte*>(start), length * sizeof(Type) };
  }

  [[nodiscard]]
  constexpr
  size_t size() const noexcept {
    return length;
  }

  [[nodiscard]]
  constexpr
  size_t size_bytes() const noexcept {
    return length * sizeof(Type);
  }

  [[nodiscard]]
  constexpr
  bool empty() const noexcept {
    return length == 0;
  }

  [[nodiscard]]
  constexpr
  decltype(auto) operator[](this auto&& self, const size_t index) noexcept {
    return *(self.data + self.index);
  }

  [[nodiscard]]
  constexpr
  decltype(auto) front(this auto&& self) noexcept {
    return *self.data;
  }

  [[nodiscard]]
  constexpr
  decltype(auto) back(this auto&& self) noexcept {
    return *(self.data + self.length - 1);
  }

  [[nodiscard]]
  constexpr
  auto begin(this auto&& self) noexcept {
    return self.data;
  }

  [[nodiscard]]
  constexpr
  auto end(this auto&& self) noexcept {
    return self.data + self.length;
  }

  Type* data = nullptr;
  size_t length{};
};

} // namespace flp

