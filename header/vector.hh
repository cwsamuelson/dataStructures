#ifndef __VECTOR_HH__
#define __VECTOR_HH__

#include<cmath>
#include<exception>
#include<string>

#include<normal_iterator.hh>

class indexOutOfBoundsException : public std::exception{
private:
  std::string msg;

public:
  indexOutOfBoundsException(unsigned long long idx){
    msg = "Index ";
    msg += idx;
    msg += " out of bounds!";
  }
  virtual const char* what() const noexcept{
    return msg.data();
  }
};

template<class T>
class vector{
public:
  typedef T value_type;
  typedef value_type* pointer;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef const value_type* const_pointer;
  typedef normal_iterator<value_type, vector> iterator;
  typedef unsigned long size_type;

private:
  size_type mSize;
  size_type mCapacity;
  unsigned char* mData;
  //polymorphic data sizes? O.o
  static const unsigned int datasize = sizeof(value_type);
  const float goldenRatio = 1.4;

  void reallocateTo(size_type size){
    unsigned char* bfr;

    mCapacity = size;
    bfr = new unsigned char[(mCapacity * datasize)];

    // copy data to new buffer
    for(size_type i = 0; i < (mSize * datasize); ++i){
      bfr[i] = mData[i];
    }

    delete[] mData;
    mData = bfr;
  }

public:
  vector():
    vector(1){
  }
  vector(size_type capacity):
    mSize(0),
    mCapacity(capacity),
    mData(new unsigned char[(mCapacity * datasize)]){
  }
  vector(const vector& other):
    mSize(other.mSize),
    mCapacity(mSize + 5),
    mData(new unsigned char[(mCapacity * datasize)]){

    for(size_type i = 0; i < (mSize * datasize); ++i){
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
  vector(pointer other, size_type size):
    mSize(size),
    mCapacity(mSize + 5),
    mData(new unsigned char[(mCapacity * datasize)]){

    for(size_type i = 0; i < (mSize * datasize); ++i){
      mData[i] = other[i];
    }
  }
  template<class inputIter>
  vector(inputIter first, inputIter last){
    for(;first != last; ++first){
      push_back(*first);
    }
  }
  virtual ~vector(){
    clear();
    delete[] mData;
  }
  
  vector& operator=(const vector& other){
    if(mCapacity < other.mSize){
      delete[] mData;
      
      mCapacity = other.mCapacity;
      mData = new unsigned char[(mCapacity * datasize)];
    }

    mSize = other.mSize;
    for(size_type i = 0; i < (mSize * datasize); ++i){
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
  reference operator[](size_type idx){
    if(idx >= mSize){
      throw indexOutOfBoundsException(idx);
    }
    return (reference)(*(mData + (idx * datasize)));
  }
  const_reference operator[](size_type idx) const{
    return (*this)[idx];
  }
  reference front(){
    return (*this)[0];
  }
  reference back(){
    return (*this)[mSize - 1];
  }
  
  //uses copy constructor to store incoming data;
  void push_back(const_reference data){
    if(mSize + 1 > mCapacity){
      reallocateTo(std::ceil(mCapacity * goldenRatio));
    }

    new ((pointer)(mData + (mSize * datasize))) value_type(data);
    ++mSize;
  }
  //forwards arguments to constructor
  template<class ...Args>
  void emplace_back(Args... args){
    if(mSize + 1 > mCapacity){
      reallocateTo(std::ceil(mCapacity * goldenRatio));
    }

    //use placement new to call ctor
    new((pointer)(mData + (mSize * datasize))) value_type(args...);
    ++mSize;
  }
  void pop_back(){
    --mSize;
    //call dtor
    ((pointer)(mData + (mSize * datasize)))->~value_type();
  }

  void clear(){
    while(mSize > 0){
      pop_back();
    }
  }
  bool empty() const{
    return mSize == 0;
  }
  size_type size() const{
    return mSize;
  }
  size_type capacity() const{
    return mCapacity;
  }
  void resize(size_type count, value_type value = value_type()){
    while(mSize < count){
      push_back(value);
    }
    while(mSize > count){
      pop_back();
    }
  }
  void reserve(size_type cap){
    if(mCapacity < cap){
      reallocateTo(cap);
    }
  }

  iterator begin(){
    return Iterator(0);
  }
  const iterator cbegin() const{
    return begin();
  }
  iterator end(){
    return Iterator(mSize);
  }
  const iterator cend() const{
    return end();
  }
  iterator Iterator(size_type idx){
    return iterator(pointer(mData + (idx * datasize)));
  }
};

#endif

