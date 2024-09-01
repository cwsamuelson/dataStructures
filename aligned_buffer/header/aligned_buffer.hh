#pragma once

#include <array>
#include <cstddef>

namespace flp {

// this must always be manually destructed
// there is no way to track the object lifetime without changing memory footprint
// from the 'contained' type, and correspondingly change alignment
// this means this is only a utility/facility class, because it cannot maintain its own invariants
template<typename Type, size_t alignment = alignof(Type)>
struct AlignedBuffer {
  static constexpr size_t Size = sizeof(Type);

  alignas(alignment)
  std::array<std::byte, Size> storage;

  template<typename ...Args>
  void construct(Args&& ...args) {
    new (storage.data()) Type(std::forward<Args>(args)...);
  }
  void destruct() {
    reinterpret_cast<Type*>(&storage)->~Type();
  }

  [[nodiscard]]
  Type& get() noexcept {
    return *reinterpret_cast<Type*>(&storage);
  }

  [[nodiscard]]
  const Type& get() const noexcept {
    return *reinterpret_cast<Type*>(&storage);
  }
};

}

