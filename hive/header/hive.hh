#pragma once

#include <aligned_buffer.hh>

#include <array>
#include <list>
#include <numeric>
#include <ranges>

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

template<typename Type, std::size_t ChunkSize = 4096>
struct Hive {
  struct Chunk {
    constexpr static std::size_t ObjectCount = ChunkSize / sizeof(Type);

    alignas(ChunkSize) std::array<AlignedTypeBuffer<Type>, ObjectCount> buffer {};
    std::array<bool, ObjectCount> validity_flags {};
    size_t                        valid_count {};

    constexpr static size_t MemoryLoss = ChunkSize - sizeof(buffer);
  };

  template<typename T>
  struct BaseIterator {
    std::list<Chunk>::iterator chunk_iterator;
    size_t                     buffer_index;

    BaseIterator operator++() {
      if (buffer_index == Chunk::ObjectCount) {
        ++chunk_iterator;
        buffer_index = 0;
      } else {
        ++buffer_index;
      }

      while ((buffer_index + 1) < Chunk::ObjectCount and not chunk_iterator->validity_flags[buffer_index]) {
        ++buffer_index;
      }
      return { chunk_iterator, buffer_index };
    }
    BaseIterator operator--() {
      if (buffer_index == 0) {
        --chunk_iterator;
        buffer_index = Chunk::ObjectCount - 1;
      } else {
        --buffer_index;
      }

      while (buffer_index > 0 and not chunk_iterator->validity_flags[buffer_index]) {
        --buffer_index;
      }
      return { chunk_iterator, buffer_index };
    }
    decltype(auto) operator*() const {
      return chunk_iterator->buffer[buffer_index].get();
    }
    decltype(auto) operator*() {
      return chunk_iterator->buffer[buffer_index].get();
    }
  };

  using iterator       = BaseIterator<Type>;
  using const_iterator = BaseIterator</*const*/ Type>;

  // list helps preserve iterators
  // allocations are done in chunks to assign with memory management
  std::list<Chunk> chunks;

  // rule of 0? 🤞🏻
  /*Hive()                = default;
  Hive(const Hive&)     = default;
  Hive(Hive&&) noexcept = default;

  Hive& operator=(const Hive&)     = default;
  Hive& operator=(Hive&&) noexcept = default;

  ~Hive() = default;*/

  // iterators
  iterator begin() noexcept {
    auto   iter  = chunks.begin();
    size_t index = 0;

    while (index < Chunk::ObjectCount and not iter->validity_flags[index]) {
      ++index;
    }

    return { iter, index };
  }
  const_iterator begin() const noexcept {
    auto   iter  = chunks.begin();
    size_t index = 0;

    while (index < Chunk::ObjectCount and not iter->validity_flags[index]) {
      ++index;
    }

    return { iter, index };
  }
  // where, precisely, does end point in this case?
  iterator end() noexcept {
    return { chunks.end(), 0 };
  }
  const_iterator end() const noexcept {
    return { chunks.end(), 0 };
  }

  const_iterator cbegin() const noexcept;
  const_iterator cend() const noexcept;

  // reverse_iterator       rbegin() noexcept;
  // const_reverse_iterator rbegin() const noexcept;
  // reverse_iterator       rend() noexcept;
  // const_reverse_iterator rend() const noexcept;

  // const_reverse_iterator crbegin() const noexcept;
  // const_reverse_iterator crend() const noexcept;

  // capacity
  [[nodiscard]]
  bool empty() const noexcept {
    return chunks.empty();
  }
  [[nodiscard]]
  size_t size() const noexcept {
    auto valid_range = std::views::transform(chunks, [](const auto& chunk) {
      return chunk.valid_count;
    });
    return std::accumulate(std::begin(valid_range), std::end(valid_range), 0ULL);
  }
  [[nodiscard]]
  size_t capacity() const noexcept {
    return chunks.size() * Chunk::ObjectCount;
  }

  // modify
  template<typename... Args>
  iterator emplace(Args&&... args) {
    // I don't think this meets the expected performance characteristics
    auto chunk_cursor = chunks.begin();

    while (chunk_cursor != chunks.end() and chunk_cursor->valid_count < Chunk::ObjectCount) {
      ++chunk_cursor;
    }

    auto& chunk = *chunk_cursor;
    for (auto& [buffer, flag] : std::views::zip(chunk.buffer, chunk.validity_flags)) {
      if (not flag) {
        buffer.construct(std::forward<Args>(args)...);
        flag = true;
        break;
      }
    }
  }

  iterator insert(const Type& value) {
    return insert(1, value);
  }
  iterator insert(size_t count, const Type& value) {
    // I don't think this meets the expected performance characteristics
    auto   chunk_cursor = chunks.begin();
    size_t final_insert_index {};

    while (count > 0) {
      while (chunk_cursor != chunks.end() and chunk_cursor->valid_count == Chunk::ObjectCount) {
        ++chunk_cursor;
      }

      if (chunk_cursor == chunks.end()) {
        chunk_cursor = chunks.emplace(chunks.end());
      }

      auto& chunk         = *chunk_cursor;
      auto  chunk_range   = std::views::zip(chunk.buffer, chunk.validity_flags);
      auto  buffer_cursor = chunk_range.begin();
      while (buffer_cursor != chunk_range.end() and count > 0 and chunk.valid_count < Chunk::ObjectCount) {
        auto [buffer, flag] = *buffer_cursor;
        if (not flag) {
          buffer.construct(value);
          flag = true;
          ++chunk.valid_count;
          --count;
          final_insert_index = buffer_cursor - chunk_range.begin();
        }
        ++buffer_cursor;
      }
    }

    return { chunk_cursor, final_insert_index };
  }

  iterator erase(const_iterator position) {
    position.chunk_iterator->buffer[position.buffer_index].destruct();
    position.chunk_iterator->validity_flags[position.buffer_index] = false;
    --position.chunk_iterator->valid_count;

    if (position.chunk_iterator->valid_count == 0) {
      chunks.erase(position.chunk_iterator);
    }

    return {};
  }

  void swap(Hive& other) noexcept {
    std::swap(chunks, other.chunks);
  }

  void clear() noexcept {
    // gotta destruct all contents first
    chunks.clear();
  }
};

} // namespace flp
