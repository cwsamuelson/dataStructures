#pragma once

#include <array>
#include <cstddef>

namespace flp {

// this must always be manually destructed
// there is no way to track the object lifetime without changing memory footprint
// from the 'contained' type, and correspondingly change alignment
// this means this is only a utility/facility class, because it cannot maintain its own invariants

template<size_t AllocationSize, size_t AllocationAlignment>
struct AlignedBuffer {
  static constexpr size_t Size = AllocationSize;

  alignas(AllocationAlignment) std::array<std::byte, Size> storage;

  template<typename Type, typename... Args>
    requires(sizeof(Type) == AllocationSize and alignof(Type) == AllocationAlignment)
  void construct(Args&&... args) {
    new (storage.data()) Type(std::forward<Args>(args)...);
  }
  template<typename Type>
  void destruct() {
    reinterpret_cast<Type*>(&storage)->~Type();
  }

  template<typename Type>
  [[nodiscard]]
  Type& get() noexcept {
    return *reinterpret_cast<Type*>(&storage);
  }

  template<typename Type>
  [[nodiscard]]
  const Type& get() const noexcept {
    return *reinterpret_cast<Type*>(&storage);
  }
};

template<typename Type>
struct AlignedTypeBuffer : AlignedBuffer<sizeof(Type), alignof(Type)> {
  using Base = AlignedBuffer<sizeof(Type), alignof(Type)>;

  template<typename... Args>
  void construct(Args&&... args) {
    Base::template construct<Type>(std::forward<Args>(args)...);
  }
  void destruct() {
    Base::template destruct<Type>();
  }

  [[nodiscard]]
  Type& get() noexcept {
    return Base::template get<Type>();
  }

  [[nodiscard]]
  const Type& get() const noexcept {
    return Base::template get<Type>();
  }
};

} // namespace flp
