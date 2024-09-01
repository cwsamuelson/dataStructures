#pragma once

#include <error_help.hh>

namespace flp {

template<typename Type, size_t alignment = alignof(Type)>
struct AlignedBuffer {
  static constexpr size_t Size = sizeof(Type);

  alignas(alignment)
  std::byte storage[Size];

  template<typename ...Args>
  void construct(Args&& ...args) {
    new (&storage) Type(std::forward<Args>(args)...);
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

