#pragma once

#include <memory>

namespace flp {

struct Allocator {
protected:
  virtual void* allocate(size_t size, size_t alignment) = 0;

  virtual void deallocate(void* pointer, size_t size) = 0;

  virtual void deallocate(void* pointer, std::align_val_t alignment) = 0;

  virtual void deallocate(void* pointer, size_t size, std::align_val_t alignment) = 0;

public:
  template<typename Type>
  Type* allocate(const size_t count){
    return static_cast<Type*>(allocate(count * sizeof(Type), alignof(Type)));
  }

  template<typename Type>
  void deallocate(Type* pointer) {
    deallocate(static_cast<void*>(pointer), static_cast<std::align_val_t>(alignof(Type)));
  }

  template<typename Type>
  void deallocate(Type* pointer, const size_t size) {
    deallocate(static_cast<void*>(pointer), size);
  }

  template<typename Type>
  void deallocate(Type* pointer, const std::align_val_t alignment) {
    deallocate(static_cast<void*>(pointer), static_cast<std::align_val_t>(alignment));
  }

  template<typename Type>
  void deallocate(Type* pointer, const size_t size, const std::align_val_t alignment) {
    deallocate(static_cast<void*>(pointer), size, alignment);
  }

  template<typename Type, typename ...Args>
  void construct(Type* pointer, Args&& ...args) {
    new (pointer) Type(std::forward<Args>(args)...);
  }

  template<typename Type, typename ...Args>
  void construct_n(Type* pointer, const size_t count, Args&& ...args) {
    // forward might do a move, making `args` invalid for subsequent iterations.
    // I feel like this is mostly the user's problem?
    for (auto* ptr = pointer; ptr != pointer + count; ++ptr) {
      construct(ptr, std::forward<Args>(args)...);
    }
  }

  template<typename Type>
  void destruct(Type* pointer) {
    pointer->~Type();
  }

  template<typename Type>
  void destruct_n(Type* pointer, const size_t count) {
    for(auto* ptr = pointer; ptr != pointer + count; ++ptr) {
      destruct(ptr);
    }
  }

  template<typename Type>
  struct Deleter {
    std::shared_ptr<Allocator> allocator;

    void operator()(Type* pointer) {
      allocator->destruct(pointer);
      allocator->deallocate(pointer);
    }
  };

  template<typename Type, typename ...Args>
  std::unique_ptr<Type, Deleter<Type>> create(Args&& ...args) {
    auto* ptr = allocate<Type>(1);
    construct(ptr, std::forward<Args>(args)...);
    return {ptr, {shared_from_this()}};
  }
};

} // namespace flp

