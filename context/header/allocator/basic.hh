#pragma once

namespace flp {

// maybe 'id allocator'?
// maybe should only be for testing?
struct STDAllocator : AllocatorBase {
  size_t id{};

  STDAllocator(const size_t ID)
    : id(ID)
  {}

  STDAllocator(const STDAllocator&) = delete;
  void operator=(const STDAllocator&) = delete;

  void* allocate(const size_t size, const size_t alignment) override {
    return operator new(size, static_cast<std::align_val_t>(alignment));
  }

  void deallocate(void* ptr, const size_t size) override {
    operator delete(ptr, size);
  }

  void deallocate(void* pointer, std::align_val_t alignment) {
    operator delete(pointer, alignment);
  }

  void deallocate(void* pointer, size_t size, std::align_val_t alignment) override {
    operator delete(pointer, size, alignment);
  }
};

}
