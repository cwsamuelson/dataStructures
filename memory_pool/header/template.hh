#pragma once


namespace flp {

struct MemoryPool {
  std::shared_ptr<unsigned char[]> memory;
  std::span<unsigned char> block;
  std::span<unsigned char> remaining_block;
  MemoryPool(const size_t block_size)
      : memory(new unsigned char[block_size])
      , block(memory.get(), block_size)
  {}

  //MemoryPool(init with a memory block)

  template<typename Type, typename ...Args>
  SharedPointer<Type> create(Args&& ...args) {
    // find next alignment
    //remaining_block = remaining_block.subspan(get_alignment(alignof(Type)));
    new (remaining_block.data()) Type(std::forward<Args>(args)...);
    return {
      remaining_block.data()
    };
  }
};

} // namespace flp

