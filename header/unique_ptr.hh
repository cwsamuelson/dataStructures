#ifndef __UNIQUE_PTR_HH__
#define __UNIQUE_PTR_HH__

template<class T>
class unique_ptr{
public:
  typedef T value_type;
  typedef value_type& reference;
  typedef value_type* pointer;

private:
  pointer mData;

public:
  unique_ptr():
    mData(nullptr){
  }
  unique_ptr(pointer ptr):
    mData(ptr){
  }
  unique_ptr(unique_ptr& other):
    mData(other.mData){
    other.mData = nullptr;
  }
  virtual ~unique_ptr(){
    if(mData){
      delete mData;
    }
  }

  unique_ptr& operator=(pointer other){
    delete mData;
    mData = other;

    return *this;
  }
  unique_ptr& operator=(unique_ptr& other){
    if(mData != other.mData){
      delete mData;
      mData = other.mData;
      other.mData = nullptr;
    }
    return *this;
  }

  bool operator==(pointer other) const{
    return (mData == other);
  }
  bool operator==(const unique_ptr& other) const{
    return (mData == other.mData);
  }
  
  reference operator*(){
    return *mData;
  }
  
  pointer operator->(){
    return mData;
  }
};

template<class T, class ... Args>
unique_ptr<T> make_unique(Args ...args){
  T* temp = new T(args...);

  return unique_ptr<T>(temp);
}

#endif

