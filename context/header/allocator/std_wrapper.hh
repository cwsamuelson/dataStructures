#pragma once

namespace flp {

template<typename Type>
struct StdAllocWrapper {
  using value_type = Type;
  using pointer = Type*;

  std::shared_ptr<AllocatorBase> allocator;

  StdAllocWrapper()
    : allocator(::allocator())
  {}

  pointer allocate(const size_t n) {
    return allocator->allocate<Type>(n);
  }

  /*pointer allocate(const size_t n, const pointer) {
    return nullptr;
  }*/

  /*pointer allocate_at_least(const size_t n) {
    return nullptr;
  }*/

  void deallocate(pointer p, size_t n) {
    allocator->deallocate<Type>(p, n);
  }

  size_t max_size() const {
    return -1;
  }

  void construct(){}
  void destroy() {}
};

}
