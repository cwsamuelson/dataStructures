#ifndef __ARRAY_HH__
#define __ARRAY_HH__

template<class T>
class array;

template<class T, unsigned int N>
class array<T[N]>{
public:
  typedef unsigned int index_t;
  const index_t size = N;
  static const unsigned int ptrdiff = sizeof(T);

private:
  char mArr[N * ptrdiff];

public:
  T& operator[](index_t idx){
    return mArr[idx * ptrdiff];
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

