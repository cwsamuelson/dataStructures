#ifndef __ALGORITHM_HH__
#define __ALGORITHM_HH__

#include<vector.hh>

template<class T>
struct less{
  bool operator()(const T& lhs, const T& rhs){
    return lhs < rhs;
  }
};

template<class iter>
unsigned long distance(iter first, iter last){
  unsigned long ret = 0;
  while(first++ != last){
    ++ret;
  }

  return ret;
}

template<class iter>
void myswap(iter x, iter y){
  auto z = *x;
  *x = *y;
  *y = z;
}

template<class iter, class compare>
void merge(iter first, iter mid, iter last, compare comp){
  vector<typename iter::value_type> vec;
  auto middle = mid;
  auto start = first;
  auto stop = last;

  while(first != middle && mid != last){
    if(comp(*mid, *first)){
      vec.push_back(*mid);
      ++mid;
    } else {
      vec.push_back(*first);
      ++first;
    }
  }
  while(first != middle){
    vec.push_back(*(first++));
  }
  while(mid != last){
    vec.push_back(*(mid++));
  }

  auto begin = vec.begin();
  for(;start != stop; ++start, ++begin){
    *start = *begin;
  }
}

template<class iter, class compare = less<typename iter::value_type> >
void sort(iter first, iter last, compare comp = less<typename iter::value_type>()){
  auto length = distance(first, last);

  if(length < 2){
    return;
  }

  auto mid = first + (length / 2);
  sort(first, mid, comp);
  sort(mid, last, comp);

  merge(first, mid, last, comp);
}

#endif

