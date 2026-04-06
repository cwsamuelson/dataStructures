#pragma once

#include <allocator/base.hh>
#include <context.hh>

#include <cstddef>
#include <memory>

namespace flp {

template<typename Type>
struct StdAllocWrapper {
  using value_type = Type;
  using pointer    = Type*;

  std::shared_ptr<AllocatorBase> allocator;

  StdAllocWrapper()
    : allocator(flp::allocator())
  {}

  template<typename Other>
  StdAllocWrapper(const StdAllocWrapper<Other>& other)
    : allocator(other.allocator)
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

  void deallocate(pointer ptr, const size_t count) {
    allocator->deallocate<Type>(ptr, count);
  }

  [[nodiscard]]
  size_t max_size() const {
    return -1;
  }

  // void construct(){}
  // void destroy() {}

  template<typename OtherType>
  friend bool operator==(const StdAllocWrapper& lhs, const StdAllocWrapper<OtherType>& rhs) {
    return lhs.allocator == rhs.allocator;
  }
};

} // namespace flp
