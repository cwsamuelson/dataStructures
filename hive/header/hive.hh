#pragma once

#include <array>
#include <list>

namespace flp {

template<typename Type, std::size_t ChunkSize = 1024>
struct hive {
  // use optional? to allow types with weird lifetime control
  // buuut, that incurs an overhead...
  // so aligned buffer?
  // or change array to be vector, and reserve memory instead
  // this doesn't solve destruction, really..

  // list helps preserve iterators
  // allocations are done in chunks to assign with memory management
  std::list<std::array<Type, ChunkSize>> data;

  size_t size;

  // free list
};

} // namespace flp
