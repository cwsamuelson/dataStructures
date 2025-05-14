#pragma once

#include <allocator/base.hh>

#include <memory>

namespace flp {

struct PoolAllocator : AllocatorBase {
  struct MemoryPool {
    std::shared_ptr<unsigned char[]> memory;

    std::span<unsigned char> whole_block;
    std::span<unsigned char> remaining_block;
  };

  MemoryPool pool;

  PoolAllocator()
    : PoolAllocator(4096)
  {}

  PoolAllocator(const size_t block_size)
    : pool({
      std::shared_ptr<unsigned char[]>{new unsigned char[block_size]},
      {pool.memory.get(), block_size},
      {pool.whole_block}
    })
  {}

  PoolAllocator(const PoolAllocator&) = delete;
  void operator=(const PoolAllocator&) = delete;

  void* allocate(const size_t size, const size_t alignment) override {
    const auto* rptr = pool.remaining_block.data();
    pool.remaining_block = pool.remaining_block.subspan(alignment - (reinterpret_cast<size_t>(rptr) % alignment));
    auto* pointer = pool.remaining_block.data();
    pool.remaining_block = pool.remaining_block.subspan(size);
    return pointer;
  }

  void deallocate([[maybe_unused]]void* ptr, [[maybe_unused]]const size_t alignment) override {
  }

  void deallocate([[maybe_unused]]void* pointer, [[maybe_unused]]const std::align_val_t alignment) {
  }

  void deallocate([[maybe_unused]]void* pointer, [[maybe_unused]]const size_t size, [[maybe_unused]]const std::align_val_t alignment) override {
  }
};

}
