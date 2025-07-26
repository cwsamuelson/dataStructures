#pragma once

#include <aligned_buffer.hh>

#include <cstdint>
#include <list>
#include <vector>

namespace flp {

// 'bucket array'

// questions:
// how should the block size be defined?
//  are we expecting it to be page size?
//  is it measured in bytes, or number of objects?
//  does the 'metadata' count?
// what is the overhead per object (1 byte for tracking validity)
//  and is that stored inline with the object
//  or next to it within the chunk (i.e. separate array/vector)

// assuming:
// chunksize targets a 'page'
//  this means we want the storage to be aligned
//  may need a custom allocator to get list to allocate aligned memory
// the metadata doesn't count towards this
// the overhead will only be 1 byte to track validity
// and this will be stored in a container next to the data
// this helps preserve alignment and contiguity of the data

template<typename Type>
struct Hive {
  struct Block {
    std::vector<AlignedTypeBuffer<Type>> data;
    // so long as a block holds less than 255 elements, a skip value will never need to be larger than `uint8_t`
    std::vector<uint8_t> skip_list;
    size_t size = 0;
  };

  struct Iterator {
    typename decltype(std::declval<Block>().skip_list)::iterator skip_it;
    typename decltype(std::declval<Block>().data)::iterator data_it;

    decltype(auto) operator*(this auto&& self) noexcept {
      return self.data_it->get();
    }
    decltype(auto) operator->(this auto&& self) noexcept {
      return &self.data_it->get();
    }
  };

  constexpr static float block_growth_factor = 1.4F;
  size_t block_size = 10;
  std::list<Block> blocks;

  void new_block() {
    auto& block = blocks.emplace_back();

    block.data.resize(block_size);
    block.skip_list.resize(block_size);

    block.skip_list.at(0) = block_size;
    block.skip_list.at(block_size - 1) = block_size;

    block_size = static_cast<size_t>(block_size * block_growth_factor);
  }

  template<typename ...Args>
  Iterator emplace(Args&&...);

  Iterator insert(const Type& value) {
    auto block_iter = blocks.begin();

    // find a block with space
    while (block_iter->size == block_iter->data.size() and block_iter != blocks.end()) {
      ++block_iter;
    }

    // allocate if necessary
    if (block_iter == blocks.end()) {
      new_block();
      block_iter = blocks.end();
      --block_iter;
    }

    auto data_it = block_iter->data.begin();
    auto skip_it = block_iter->skip_list.begin();

    while (*skip_it == 0) {
      ++data_it;
      ++skip_it;
    }

    data_it->construct(value);
    const auto current_block_size = *skip_it;
    const auto new_block_size = current_block_size - 1;

    const auto new_block_begin = skip_it + 1;
    const auto new_block_end = (skip_it + current_block_size);

    *skip_it = 0;
    *new_block_begin = new_block_size;
    *new_block_end = new_block_size;

    return {skip_it, data_it};
  }
  Iterator insert(Type&&);

  void erase(Iterator);
  void erase(Iterator, Iterator);

  void splice(Hive&& other) {
    blocks.splice(blocks.end(), other.blocks);
  }

  [[nodiscard]]
  bool empty() const noexcept {
    return blocks.empty();
  }
  [[nodiscard]]
  size_t size() const noexcept;
  void clear() {
    // first must destruct all objects
    blocks.clear();
  }
};

} // namespace flp
