#pragma once

#include <utility>

namespace flp {

template<typename Type>
struct UniquePointer {
  constexpr
  UniquePointer() noexcept = default;

  constexpr
  UniquePointer(Type* ptr) noexcept
    : pointer(ptr)
  {}

  UniquePointer(const UniquePointer&) = delete;
  void operator=(const UniquePointer&) = delete;

  constexpr
  UniquePointer(UniquePointer&& other) noexcept
    : pointer(std::exchange(other.pointer, nullptr))
  {}

  constexpr
  UniquePointer& operator=(UniquePointer&& other) noexcept {
    pointer = std::exchange(other.pointer, nullptr);

    return *this;
  }

  ~UniquePointer() noexcept {
    if (pointer != nullptr) {
      delete pointer;
    }
  }

  Type* pointer = nullptr;
};

} // namespace flp
