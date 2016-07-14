#ifndef __MEMORY_POOL_HH__
#define __MEMORY_POOL_HH__

#include<list>

template<class T>
class memoryPool{
public:
    typedef T type;

private:
  class slot{
  public:
    type* start;
    type* end;
   
    slot(type* first, type* second):
      start(first),
      end(second){
    }
    
    bool operator<(const slot& rhs){
      return start < rhs.start;
    }
  };
 
  type* mStorageStart;
  void* mStorageEnd;
  unsigned int mSize;
  unsigned int mInUse;
  std::list<slot> mSlots;
 
public:
  memoryPool(size_t size):
    mStorageStart(new type[size]),
    mStorageEnd(mStorageStart + size - 1),
    mSize(size),
    mInUse(0){
  }
  virtual ~memoryPool(){ delete[] mStorageStart; }
  
  type* allocate(size_t amt){
    type* ret = nullptr;
    //If the request is larger than that available, return null;
    if(amt == 0 || (amt > (mSize - mInUse)) ){
      ret = nullptr;
    }else{
      //Determine where free memory exists to return;
      //If there's no memory in use, return beginning;
      if(mSlots.size() == 0){
        mSlots.emplace_back(mStorageStart, mStorageStart + amt);
        ret = mStorageStart;
      } else if(mSlots.begin()->start != mStorageStart){
        if((size_t)(mSlots.begin()->start - mStorageStart) >= amt){
          mSlots.emplace_back(mStorageStart, mStorageStart + amt);
          ret = mStorageStart;
        }
      } else {
        auto first = mSlots.begin();
        for(auto second = ++mSlots.begin(); second != mSlots.end(); ++second, ++first){
          if((size_t)(second->start - first->end) >= amt){
            ret = first->end;
            break;
          }
        }
        //If we get to the end of the list and there's no free space found, check the tail end;
        if((size_t)((mStorageStart + mSize) - first->end) >= amt){
          mSlots.emplace_back(first->end, first->end + amt);
          ret = first->end;
        }
      }
      //Only re-sort when new things have been added;
      mSlots.sort();
    }
    
    return ret;
  }
  
  void deallocate(type* ptr){
    for(auto it = mSlots.begin(); it != mSlots.end(); ++it){
      if(it->start == ptr){
        mSlots.erase(it);
        break;
      }
    }
  }
};


#endif

