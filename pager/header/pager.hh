#ifndef GALACTICSTRUCTURES_PAGER_HH
#define GALACTICSTRUCTURES_PAGER_HH

#include <cstdio>
#include <memory>
#include <map>
#include <chrono>

namespace gsw {

/*!
 * @tparam T
 *
 * @todo generalize the page file
 * ultimately the user should decide exactly what happens when data is paged in and out
 * and possibly how victim pages are chosen?
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
  struct PageMetadata{
    std::chrono::system_clock::time_point last_access;
  };
  size_t mPageSize;
  size_t mPageCount;
  ptr_type mPageMemory;
  std::map<size_t, size_t> mMemoryMap; /**< map of item index to memory index */
  std::map<size_t, std::FILE*> mFileMap;
  std::map<size_t, PageMetadata> mMetaData;

  size_t victimize(){
    //lru
    auto min = std::min_element(mMetaData.begin(), mMetaData.end(),
      [](const std::pair<size_t, PageMetadata>& l, const std::pair<size_t, PageMetadata>& r){
        return l.second.last_access < r.second.last_access;
      }
    );
    return min->first;
  }

  void save_page(size_t page_id){
    std::FILE* f;
    if(mFileMap.count(page_id) == 0){
      mFileMap[page_id] = tmpfile();
    }

    f = mFileMap[page_id];

    std::rewind(f);

    for(size_t i = 0; i < mPageSize; ++i){
      char arr[sizeof(value_type)];
      std::memcpy(arr, &mPageMemory[i], sizeof(value_type));

      for(size_t j = 0; j < sizeof(value_type); ++j){
        std::fputc(arr[j], f);
      }
    }
  }

  void load_page(size_t dst_page_id, size_t src_page_id){
    if(mFileMap.count(src_page_id) == 0) return;

    std::FILE* f = mFileMap.at(src_page_id);
    auto offset = mMemoryMap.at(dst_page_id);

    std::rewind(f);

    for(size_t i = 0; i < sizeof(value_type) * mPageSize; ++i){
      mPageMemory[i + offset] = char(std::fgetc(f));
    }
  }

  void page_fault(index_t page_id){
    auto victim_page_id = victimize();
    save_page(victim_page_id);
    load_page(victim_page_id, page_id);

    auto offset = mMemoryMap.at(victim_page_id);
    mMetaData.erase(victim_page_id);
    mMemoryMap.erase(victim_page_id);
    mMemoryMap.insert({page_id, offset});
  }

  auto getPageId(size_t idx) const{
    return (idx - (idx % mPageSize)) / mPageSize;
  }

  auto getPageOffset(size_t idx) const{
    return idx % mPageSize;
  }

public:
  explicit
  pager(size_t object_count)
    : pager(object_count, object_count)
  {}

  explicit
  pager(size_t object_count, size_t page_size, size_t page_count = 1)
    : mPageSize(page_size)
    , mPageCount(page_count)
    , mPageMemory(std::make_unique<value_type[]>(allocatedMemory()))
  {
    //! @todo check for allocating more objects than requested
    for(size_t i = 0; i < mPageCount; ++i){
      mMemoryMap[i] = i * page_size;
    }
  }

  [[nodiscard]]
  value_type& operator[](index_t idx){
    auto page_id = getPageId(idx);
    if(mMemoryMap.count(page_id) > 0){
      mMetaData[page_id].last_access = std::chrono::system_clock::now();
      return mPageMemory[mMemoryMap[page_id] + getPageOffset(idx)];
    } else {
      page_fault(page_id);
      return (*this)[idx];
    }
  }

  [[nodiscard]]
  size_t allocatedMemory() const{
    return mPageSize * mPageCount;
  }
};

}

#endif //GALACTICSTRUCTURES_PAGER_HH
