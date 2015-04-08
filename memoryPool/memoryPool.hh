#ifndef __MEMORYPOOL_H__
#define __MEMORYPOOL_H__

#include<list>

template<class T>
class memoryPool{
private:
  class slot{
  public:
    T* start;
    T* end;
   
    slot(T* first, T* second):
      start(first),
      end(second){
    }
    
    bool operator<(slot rhs){
      return this->start < rhs.start;
    }
  };
 
  T* storage;
  T* storageEnd;
  unsigned int size;
  unsigned int inUse;
  std::list<slot>slots;
 
public:
  memoryPool(size_t size):
    storage(new T[size]),
    storageEnd(storage + size - 1),
    size(size),
    inUse(0){
  }
  virtual ~memoryPool(){ delete[] this->storage; }
  
  T* allocate(size_t amt);
  void deallocate(T* ptr);
};

#include"memoryPool.cc"

#endif
