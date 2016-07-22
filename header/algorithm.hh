#ifndef __SORT_HH__
#define __SORT_HH__

template<class T>
struct less{
  bool operator<(const T& lhs, const T& rhs){
    return lhs < rhs;
  }
};

template<class iter>
unsigned long distance(iter first, iter last){
  unsigned long ret = 0;
  while(first++ != last){
    ++ret;
  }
}

template<class iter>
void swap(iter x, iter y){
  auto z = x;
  *x = *y;
  *y = *z;
}

template<class iter, class compare>
void merge(iter first, iter mid, iter last, compare comp){
  auto middle = mid;

  while(first != middle && mid != last){
    if(comp(*mid, *first)){
      swap(first, mid);
      ++mid;
    }
    ++first;
  }
}

template<class iter, class compare>
void sort(iter first, iter last, compare comp = less<iter::value_type>){
  auto length = distance(first, last);

  if(length < 2){
    return;
  }

  auto mid = first + (length / 2);
  sort(first, mid, comp);
  sort(mid, last, comp);

  merge(first, mid, last);
}

#endif

