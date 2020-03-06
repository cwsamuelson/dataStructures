#ifndef GALACTICSTRUCTURES_PAGER_HH
#define GALACTICSTRUCTURES_PAGER_HH

#include <fstream>
#include <memory>
#include <map>

namespace gsw {

/*!
 * @tparam T
 *
 * @todo generalize the page file
 * ultimately the user should decide exactly what happens when data is paged in and out
 */
template<typename T, typename F = std::fstream>
class pager
{
public:
  using value_type = T;
  using page_file_t = F;
  using index_t = size_t;
  using ptr_type = std::unique_ptr<value_type[]>;

private:
  size_t mPageSize;
  size_t mPageCount;
  ptr_type mPageMemory;
  std::map<size_t, size_t> mMemoryMap; /**< map of item index to memory index */

  int victimize(){
  }

  void page_fault(index_t idx){
    auto victim_page = victimize();
  }

  auto getPageId(size_t idx) const{
    return idx - (idx % mPageSize);
  }

  auto getPageOffset(size_t idx) const{
    return idx % mPageSize;
  }

public:
  explicit
  pager(size_t object_count, size_t page_size = 100, size_t page_count = 1)
    : mPageSize(page_size)
    , mPageCount(page_count)
    , mPageMemory(std::make_unique<value_type[]>(allocatedMemory()))
  {
    //! @todo check for allocating more objects than requested
    for(size_t i = 0; i < mPageCount; ++i){
      mMemoryMap[i] = i * page_size;
    }
  }

  value_type& operator[](index_t idx){
    auto page_id = getPageId(idx);
    if(mMemoryMap.count(page_id) > 0){
      return mPageMemory[mMemoryMap[page_id] + getPageOffset(idx)];
    } else {
      throw std::runtime_error("Page fault! What do?");
    }
  }

  [[nodiscard]]
  size_t allocatedMemory() const{
    return mPageSize * mPageCount;
  }
};

}

#endif //GALACTICSTRUCTURES_PAGER_HH
