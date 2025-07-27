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
    using value_type = Type;
    using difference_type = std::ptrdiff_t;
    using pointer = Type*;
    using reference = Type&;
    using iterator_category = std::bidirectional_iterator_tag;

    Hive* hive;
    typename decltype(std::declval<Hive>().blocks)::iterator block_it;
    size_t index;

    friend bool operator==(const Iterator& lhs, const Iterator& rhs) noexcept = default;
    friend auto operator<=>(const Iterator& lhs, const Iterator& rhs) noexcept = default;

    decltype(auto) operator*(this auto&& self) noexcept {
      return self.block_it->data.at(self.index).get();
    }
    decltype(auto) operator->(this auto&& self) noexcept {
      return &self.block_it->data.at(self.index).get();
    }

    Iterator& operator++() noexcept {
      ++index;

      index += block_it->skip_list.at(index);

      if (index == block_it->data.size()) {
        ++block_it;
        index = 0;
      }

      return *this;
    }

    Iterator operator++(int) noexcept {
      Iterator copy = *this;
      ++(*this);
      return copy;
    }

    Iterator& operator--() noexcept {
      if (index == 0) {
        --block_it;
        index = block_it->skip_list.size() - 1;
        return *this;
      }

      --index;

      return *this;
    }

    Iterator operator--(int) noexcept {
      Iterator copy = *this;
      --(*this);
      return copy;
    }
  };

  void new_block() {
    auto& block = blocks.emplace_back();

    block.data.resize(block_size);
    block.skip_list.resize(block_size);

    block.skip_list.at(0) = block_size;
    block.skip_list.at(block_size - 1) = block_size;

    block_size = static_cast<size_t>(block_size * block_growth_factor);
  }

  template<typename ...Args>
  Iterator emplace(Args&&... args) {
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

    data_it->construct(std::forward<Args>(args)...);
    const auto current_block_size = *skip_it;
    const auto new_block_size = current_block_size - 1;

    const auto new_block_begin = skip_it + 1;
    const auto new_block_end = (skip_it + current_block_size - 1);

    *skip_it = 0;
    *new_block_begin = new_block_size;
    *new_block_end = new_block_size;

    return { this, block_iter, data_it - block_iter->data.begin() };
  }

  Iterator insert(const Type& value) {
    return emplace(value);
  }
  Iterator insert(Type&& value) {
    return emplace(std::move(value));
  }

  void erase(Iterator position) {
    position.block_it->data.at(position.index).destruct();

    // if position is next to any empty blocks, extend them

    const auto pre_index = position.index == 0 ? 0 : position.index - 1;
    const auto post_index = position.index == position.block_it->skip_list.size() - 1 ? position.block_it->skip_list.size() - 1 : position.index + 1;

    if (  position.index != 0
      and position.block_it->skip_list.at(pre_index) != 0
      and position.index != position.block_it->skip_list.size() - 1
      and position.block_it->skip_list.at(post_index) != 0) {
      // empty on both sides
      const auto block_start = pre_index - position.block_it->skip_list.at(pre_index) + 1;
      const auto block_finish = post_index + position.block_it->skip_list.at(post_index) - 1;
      const auto new_block_size = block_finish - block_start;
      // update block start
      position.block_it->skip_list.at(block_start) = new_block_size;
      // update block end
      position.block_it->skip_list.at(block_finish) = new_block_size;
    } else if (position.index != 0 and position.block_it->skip_list.at(pre_index) != 0) {
      // empty block before
      const auto block_start = pre_index - position.block_it->skip_list.at(pre_index) + 1;
      const auto new_block_size = position.block_it->skip_list.at(pre_index) + 1;
      // update block start
      position.block_it->skip_list.at(block_start) = new_block_size;
      position.block_it->skip_list.at(position.index) = new_block_size;
      position.block_it->skip_list.at(pre_index) = 0;
    } else if (position.index != position.block_it->skip_list.size() - 1 and position.block_it->skip_list.at(post_index) != 0) {
      // empty block after
      const auto block_finish = post_index + position.block_it->skip_list.at(post_index) - 1;
      const auto new_block_size = position.block_it->skip_list.at(post_index) + 1;

      // update block start
      position.block_it->skip_list.at(block_finish) = new_block_size;
      position.block_it->skip_list.at(position.index) = new_block_size;
      position.block_it->skip_list.at(post_index) = 0;
    } else {
      // new single block
      position.block_it->skip_list.at(position.index) = 1;
    }

    // erase block?
  }
  void erase(Iterator first, Iterator last) {
    while (first != last) {
      erase(first);
      ++first;
    }
  }

  void splice(Hive& other) {
    blocks.splice(blocks.end(), other.blocks);
  }

  [[nodiscard]]
  bool empty() const noexcept {
    return blocks.empty();
  }

  [[nodiscard]]
  size_t size() const noexcept {
    size_t count{};
    for (const auto& block : blocks) {
      count += count_in_block(block);
    }
    return count;
  }
  void clear() noexcept(std::is_nothrow_destructible_v<Type>) {
    for (auto iter = begin(); iter != end(); ++iter) {
      iter.block_it->data.at(iter.index).destruct();
    }

    blocks.clear();
  }

  decltype(auto) begin(this auto&& self) noexcept {
    return Iterator { &self, self.blocks.begin(), 0 };
  }

  decltype(auto) end(this auto&& self) noexcept {
    return Iterator {  &self,self.blocks.end(), 0 };
  }

  [[nodiscard]]
  size_t count_in_block(const Block& block) const noexcept {
    size_t count{};
    size_t index{};
    while (index < block.data.size()) {
      while (index < block.data.size() and block.skip_list.at(index) == 0) {
        ++count;
        ++index;
      }
      while (index < block.skip_list.size() and block.skip_list.at(index) != 0) {
        index += block.skip_list.at(index);
      }
    }

    return count;
  }

  constexpr static float block_growth_factor = 1.4F;
  size_t block_size = 10;
  std::list<Block> blocks;
};

} // namespace flp
