#pragma once

#include <aligned_buffer.hh>

#include <cstdint>
#include <format>
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

//! @TODO allocator awareness

template<typename Type, bool IsConst>
using ConditionalConst = std::conditional_t<IsConst, const Type, Type>;

template<typename Type>
struct Hive {
  template<bool IsConst>
  struct Iterator;

  using value_type = Type;
  using size_type = size_t;
  using difference_type = ptrdiff_t;
  using reference = Type&;
  using const_reference = const Type&;
  using pointer = Type*;
  using const_pointer = const Type*;
  using iterator = Iterator<false>;
  using const_iterator = Iterator<true>;

  struct Block {
    std::vector<AlignedTypeBuffer<Type>> data;
    std::vector<uint16_t> skip_list;
    size_t size = 0;
  };

  template<bool IsConst>
  struct Iterator {
    using value_type = Type;
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::bidirectional_iterator_tag;
    using pointer = ConditionalConst<Type, IsConst>*;
    using reference = ConditionalConst<Type, IsConst>&;

    using Container = ConditionalConst<Hive, IsConst>;
    using BlockIterator = typename decltype(std::declval<Hive>().blocks)::iterator;

    Container* hive = nullptr;
    BlockIterator block_it;
    size_t index{};

    Iterator(Container* container, BlockIterator iter, size_t idx)
      : hive(container)
      , block_it(iter)
      , index(idx)
    {}

    Iterator() noexcept = default;
    Iterator(const Iterator&) = default;
    Iterator(Iterator&&) noexcept = default;
    Iterator& operator=(const Iterator&) = default;
    Iterator& operator=(Iterator&&) noexcept = default;
    ~Iterator() noexcept = default;

    Iterator(const Iterator<false>& other)
      requires (IsConst) // otherwise it's a duplicate definition
      : hive(other.hive)
      , block_it(other.block_it)
      , index(other.index)
    {}
    Iterator(Iterator<false>&& other) noexcept
      requires (IsConst) // otherwise it's a duplicate definition
      : hive(other.hive)
      , block_it(std::move(other.block_it))
      , index(other.index)
    {}
    Iterator& operator=(const Iterator<false>& other)
      requires (IsConst) {
      hive = other.hive;
      block_it = other.block_it;
      index = other.index;
      return *this;
    }
    Iterator& operator=(Iterator<false>&& other) noexcept
      requires (IsConst) {
      hive = other.hive;
      block_it = std::move(other.block_it);
      index = other.index;
      return *this;
    }

    friend bool operator==(const Iterator& lhs, const Iterator& rhs) noexcept = default;
    friend auto operator<=>(const Iterator& lhs, const Iterator& rhs) noexcept = default;

    reference operator*(this auto&& self) noexcept {
      return self.block_it->data.at(self.index).get();
    }
    pointer operator->(this auto&& self) noexcept {
      return &self.block_it->data.at(self.index).get();
    }

    Iterator& operator++() noexcept {
      if (block_it == hive->blocks.end()) {
        return *this;
      }

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

  Hive() noexcept = default;
  Hive(const Hive& other);
  Hive(Hive&& other) noexcept;
  Hive(size_t capacity);
  Hive(const size_t count, const Type& value);
  template<typename Iter1, typename Iter2>
  Hive(Iter1, Iter2);
  template<typename Range>
  Hive(Range&&);
  Hive(std::initializer_list<Type>);
  // Plus each of the above with a 'limits' parameter included

  Hive& operator=(const Hive& other);
  Hive& operator=(Hive&& other) noexcept;

  ~Hive() noexcept(noexcept(clear())) {
    clear();
  }

  template<typename ...Args>
  iterator emplace(Args&&... args) {
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

  iterator insert(const Type& value) {
    return emplace(value);
  }
  iterator insert(Type&& value) {
    return emplace(std::move(value));
  }
  template<typename Iter1, typename Iter2>
  iterator insert(Iter1 first, Iter2 last) {
    Iterator iter = end();
    for (auto value_iter = first; value_iter != last; ++value_iter) {
      iter = emplace(*value_iter);
    }
    return iter;
  }

  void erase(iterator position) {
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
      const auto new_block_size = block_finish - block_start + 1;
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

    // erase block
    if (position.block_it->skip_list.at(0) == position.block_it->skip_list.size()) {
      position.hive->blocks.erase(position.block_it);
    }
  }
  void erase(iterator first, const_iterator last) {
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
      count += count_block_size(block);
    }
    return count;
  }
  void clear() noexcept(std::is_nothrow_destructible_v<Type>) {
    for (auto iter = begin(); iter != end(); ++iter) {
      iter.block_it->data.at(iter.index).destruct();
    }

    blocks.clear();
  }
  [[nodiscard]]
  size_t capacity() const noexcept {
    size_t count{};
    for (const auto& block : blocks) {
      count += block.data.size();
    }
    return count;
  }
  void reserve(size_t capacity) {
  }
  void shrink_to_fit() {
  }
  // logically const, but would require making `blocks` mutable, which I'd
  //  rather not do for just a single function
  void compact() /*const*/ {
  }
  void swap(Hive& other) noexcept {
  }

  auto begin(this auto&& self) noexcept {
    return Iterator<std::is_const_v<decltype(self)>>(&self, self.blocks.begin(), 0);
  }
  auto end(this auto&& self) noexcept {
    return Iterator<std::is_const_v<decltype(self)>>(&self,self.blocks.end(), 0);
  }

private:
  friend std::formatter<Hive>;

  void new_block() {
    auto& block = blocks.emplace_back();

    block.data.resize(block_size);
    block.skip_list.resize(block_size);

    block.skip_list.at(0) = block_size;
    block.skip_list.at(block_size - 1) = block_size;

    block_size = static_cast<size_t>(block_size * block_growth_factor);
  }

  [[nodiscard]]
  size_t count_block_size(const Block& block) const noexcept {
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

namespace std {

template<typename Type>
void swap(const flp::Hive<Type>& x, const flp::Hive<Type>& y) noexcept(noexcept(x.swap(y))) {
  x.swap(y);
}

}

template<typename Type>
struct std::formatter<flp::Hive<Type>> : std::formatter<std::string_view> {
  bool debug_format = false;

  constexpr auto parse(std::format_parse_context& context) {
    auto iterator = context.begin();
    while (iterator != context.end() and *iterator != '}') {
      switch (*iterator) {
      case '#':
        debug_format = true;
        break;
      default:
        throw std::format_error("invalid format specifier for `flp::Hive`");
        break;
      }

      ++iterator;
    }

    if (iterator == context.end() or *iterator != '}') {
      throw std::format_error("invalid format");
    }

    return iterator;
  }

  constexpr auto format(const flp::Hive<Type>& hive, std::format_context& context) const {
    if (debug_format) {
      std::string placeholder;
      std::format_to(std::back_inserter(placeholder), "(Size: {} Capacity: {}) [", hive.size(), hive.capacity());

      for (const auto& block : hive.blocks) {
        for (size_t i{}; i < block.data.size(); ++i) {
          if (block.skip_list.at(i) == 0) {
            std::format_to(std::back_inserter(placeholder), "{} ", block.data.at(i).get());
          } else {
            for (size_t j{}; j < block.skip_list.at(i); ++j) {
              std::format_to(std::back_inserter(placeholder), "X ", block.data.at(i + j).get());
            }
            i += block.skip_list.at(i) + 1;
          }
        }
      }

      std::format_to(std::back_inserter(placeholder), "]");
      return std::formatter<std::string_view>::format(placeholder, context);
    } else {
      std::string placeholder;
      std::format_to(std::back_inserter(placeholder), "[ ");

      for (const auto& element : hive) {
        std::format_to(std::back_inserter(placeholder), "{} ", element);
      }

      std::format_to(std::back_inserter(placeholder), "]");
      return std::formatter<std::string_view>::format(placeholder, context);
    }
  }
};
