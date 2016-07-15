#ifndef __VECTOR_HH__
#define __VECTOR_HH__

#include<cmath>

#include<normal_iterator.hh>

template<class T>
class vector{
public:
  typedef T value_type;
  typedef value_type* pointer;
  typedef value_type& reference;
  typedef const reference const_reference;
  typedef const pointer const_pointer;
  typedef normal_iterator<value_type, vector> iterator;

private:
  unsigned long mSize;
  unsigned long mCapacity;
  unsigned char* mData;
  //polymorphic data sizes? O.o
  const unsigned int datasize = sizeof(value_type);
  const float goldenRatio = 1.4;

public:
  vector():
    mSize(0),
    mCapacity(1){
    mData = new unsigned char[(mCapacity * datasize)];
  }
  vector(unsigned int capacity):
    mSize(0),
    mCapacity(capacity){
    mData = new unsigned char[(mCapacity * datasize)];
  }
  vector(const vector& other):
    mSize(other.mSize),
    mCapacity(mSize + 5){
    mData = new unsigned char[(mCapacity * datasize)];
    for(unsigned long i = 0; i < (mSize * datasize); ++i){
      mData[i] = other.mData[i];
    }
  }
  vector(vector&& other):
    mSize(other.mSize),
    mCapacity(other.mCapacity),
    mData(other.mData){
    other.mSize = 0;
    other.mCapacity = 0;
    other.mData = nullptr;
  }
  vector(value_type* other, unsigned int size):
    mSize(size),
    mCapacity(mSize + 5){
    mData = new unsigned char[(mCapacity * datasize)];
    for(unsigned int i = 0; i < (mSize * datasize); ++i){
      mData[i] = other[i];
    }
  }
  virtual ~vector(){
    while(mSize > 0){
      pop_back();
    }
    delete[] mData;
  }
  
  vector& operator=(const vector& other){
    if(mCapacity < other.mSize){
      delete[] mData;
      
      mCapacity = other.mCapacity;
      mData = new unsigned char[(mCapacity * datasize)];
    }

    mSize = other.mSize;
    for(unsigned int i = 0; i < (mSize * datasize); ++i){
      mData[i] = other.mData[i];
    }

    return *this;
  }
  vector& operator=(vector&& other){
    mSize = other.mSize;
    mCapacity = other.mCapacity;
    mData = other.mData;
    
    other.mSize = 0;
    other.mCapacity = 0;
    other.mData = nullptr;
    
    return *this;
  }
  value_type& operator[](unsigned int idx){
    return (value_type&)(*(mData + (idx * datasize)));
  }
  const reference operator[](unsigned int idx) const{
    return (value_type&)(*(mData + (idx * datasize)));
  }
  
  void push_back(const value_type& data){
    // reallocate
    if(mSize + 1 > mCapacity){
      unsigned char* bfr;

      mCapacity = std::ceil(mCapacity * goldenRatio);
      bfr = new unsigned char[(mCapacity * datasize)];

      // copy data to new buffer
      for(unsigned int i = 0; i < (mSize * datasize); ++i){
        bfr[i] = mData[i];
      }
      delete[] mData;
      mData = bfr;
    }
    (value_type&)(*(mData + (mSize * datasize))) = data;
    ++mSize;
  }
  template<class ...Args>
  void emplace_back(Args... args){
    if(mSize + 1 > mCapacity){
      unsigned char* bfr;

      mCapacity = std::ceil(mCapacity * goldenRatio);
      bfr = new unsigned char[(mCapacity * datasize)];

      // copy data to new buffer
      for(unsigned int i = 0; i < (mSize * datasize); ++i){
        bfr[i] = mData[i];
      }
      delete[] mData;
      mData = bfr;
    }
    new((value_type*)(mData + (mSize * datasize))) value_type(args...);
    ++mSize;
  }
  void pop_back(){
    --mSize;
    ((value_type*)(mData + (mSize * datasize)))->~value_type();
  }
  unsigned int size() const{
    return mSize;
  }
  unsigned int capacity() const{
    return mCapacity;
  }
  iterator begin(){
    return Iterator(0);
  }
  iterator end(){
    return Iterator(mSize);
  }
  iterator Iterator(unsigned int idx){
    return iterator(pointer(mData + (idx * datasize)));
  }
};

#endif

