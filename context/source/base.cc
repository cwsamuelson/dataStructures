#include <allocator/base.hh>

void* operator new(size_t size, const std::shared_ptr<flp::AllocatorBase>& allocator) {
  return allocator->allocate(size, static_cast<size_t>(alignof(std::max_align_t)));
}

void* operator new[](size_t size, const std::shared_ptr<flp::AllocatorBase>& allocator) {
  return allocator->allocate(size, static_cast<size_t>(alignof(std::max_align_t)));
}

void* operator new(size_t size, std::align_val_t alignment, const std::shared_ptr<flp::AllocatorBase>& allocator) {
  return allocator->allocate(size, static_cast<size_t>(alignment));
}

void* operator new[](size_t size, std::align_val_t alignment, const std::shared_ptr<flp::AllocatorBase>& allocator) {
  return allocator->allocate(size, static_cast<size_t>(alignment));
}
