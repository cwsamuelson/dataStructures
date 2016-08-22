#ifndef __ARRAY_HH__
#define __ARRAY_HH__

#include<functional>
#include<vector>

//see mask_array and indirect array for indexing ideas
//  one allows data[data > 5] = -1 kinda syntax,
//  the other data[data2] = -2 syntax
//  each modifies a set of values
//  the first says values at indexes greater than 5 are set to -1
//  the other says values at indexes stored in data2 are set to -2

template<class T>
class array;

template<class T>
struct splice_index{
  typedef std::function<bool(T,T)> opsig;

  opsig mOp;
  unsigned int mIdx;

  splice_index(opsig op, unsigned int idx):
    mOp(op),
    mIdx(idx){
  }
};

template<class T>
struct splice_helper;

template<class T, unsigned int N>
struct splice_helper<T[N]>{
  array<T[N]>& mArr;
  std::vector<unsigned int> mIdxs;

  splice_helper(array<T[N]>& arr):
    mArr(arr){
  }

  array<T[N]>& operator=(T t){
    for(auto it:mIdxs){
      mArr[it] = t;
    }

    return mArr;
  }
};

template<class T, unsigned int N>
class array<T[N]>{
public:
  typedef unsigned int index_t;
  const index_t mSize = N;
  static const unsigned int ptrdiff = sizeof(T);
  typedef splice_index<T> splicer;
  typedef splice_helper<T[N]> helper;

private:
  char mArr[N * ptrdiff];

public:
  T& operator[](index_t idx){
    return mArr[idx * ptrdiff];
  }
  index_t size(){
    return mSize;
  }

  helper operator[](const splicer& si){
    helper h(*this);
    for(unsigned int i = 0; i < mSize; ++i){
      if(si.mOp(i, si.mIdx)){
        h.mIdxs.push_back(i);
      }
    }

    return h;
  }
  splicer operator>(index_t idx){
    return splicer(std::greater<T>(), idx);
  }
  splicer operator<(index_t idx){
    return splicer(std::less<T>(), idx);
  }
};

template<class T, unsigned int N>
std::ostream& operator<<(std::ostream& os, const array<T[N]>& arr){
  for(unsigned int i = 0; i < N; ++i){
    os << arr[i];
  }

  return os;
}

#endif

