#ifndef __ARC_PTR__
#define __ARC_PTR__

template<class T>
class arc_ptr{
private:
  T* pData;
  unsigned long long* count;
public:
  arc_ptr(T* pValue):pData(pValue), count(new unsigned long long(1)){  }

  ~arc_ptr(){
    --*this->count;
    if(*this->count == 0){
      delete this->pData;
    }
  }

  arc_ptr<T>& operator= (const arc_ptr<T>& sp){
    if(this != &sp){
      if(--*(this->count) == 0){
        delete this->pData;
        delete this->count;
      }
      this->pData = sp.pData;
      this->count = sp.count;
      ++*(this->count);
    }
    return *this;
  }
};

#endif

