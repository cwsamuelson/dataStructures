#pragma once

#include <cstddef>
#include <limits>

namespace flp {

// bounded span
template<typename Type, size_t Length = std::numeric_limits<size_t>::max()>
struct Span {
  Span();

  auto begin() {
    return start;
  }

  auto end() {
    return finish;
  }

  Type* start = nullptr;
  Type* finish = nullptr;
};

// unbounded span
template<typename Type>
struct Span<Type, std::numeric_limits<size_t>::max()> {
  Span() = default;

  auto begin() {
    return data;
  }

  auto end() {
    return nullptr;
  }

  Type* data = nullptr;
};

} // namespace flp

