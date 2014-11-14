#ifndef __SMART_PTR__
#define __SMART_PTR__

namespace Jing{

//Single ownership smart pointer
template<class T>
class smart_ptr{
private:
  T* pData; // Generic pointer to be stored
public:
  smart_ptr(T* pValue = 0):pData(pValue){  }
  ~smart_ptr(){ if(!pData) delete pData; }

  T& operator*(){ return *pData; }
  T* operator->(){ return pData; }
  virtual smart_ptr<T>& operator=(smart_ptr<T>& sp){
    if(this != &sp){
      if(!pData)
        delete pData;
      pData = sp.pData;
      sp.pData = 0;
    }
    return *this;
  }
};

}

#endif

