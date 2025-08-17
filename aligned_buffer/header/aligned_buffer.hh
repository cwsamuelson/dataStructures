#pragma once

#include <array>
#include <cstddef>
#include <new>

namespace flp {

// `destruct` must always manually be called.
// there is no way to track the object lifetime without changing memory footprint
// from the 'contained' type and correspondingly changing alignment.
// This means this is only a utility/facility class because it cannot maintain its own invariants.

template<size_t AllocationSize, size_t AllocationAlignment>
struct AlignedBuffer {
  static constexpr size_t Size = AllocationSize;
  static constexpr size_t Alignment = AllocationAlignment;

  alignas(Alignment) std::array<std::byte, Size> storage;
};

template<typename Type>
struct AlignedTypeBuffer : AlignedBuffer<sizeof(Type), alignof(Type)> {
  using Base = AlignedBuffer<sizeof(Type), alignof(Type)>;

  template<typename... Args>
  Type* construct(Args&&... args) noexcept(std::is_nothrow_constructible_v<Type, Args...>) {
    return new (Base::storage.data()) Type(std::forward<Args>(args)...);
  }

  void destruct() noexcept(std::is_nothrow_destructible_v<Type>) {
    std::launder<Type>(reinterpret_cast<Type*>(Base::storage.data()))->~Type();
  }

  [[nodiscard]]
  Type& get() noexcept {
    return *std::launder<Type>(reinterpret_cast<Type*>(Base::storage.data()));
  }

  [[nodiscard]]
  const Type& get() const noexcept {
    return *std::launder<const Type>(reinterpret_cast<const Type*>(Base::storage.data()));
  }
};

} // namespace flp
