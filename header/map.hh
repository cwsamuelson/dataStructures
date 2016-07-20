#ifndef __MAP_HH__
#define __MAP_HH__

#include<algorithm>
#include<exception>
#include<functional>

#include<vector.hh>
#include<tuple.hh>

class keyNotFoundException : public std::exception{
};

template<class KEY, class VALUE, class COMPARE = std::less<KEY> >
class map{
public:
  typedef KEY key_type;
  typedef VALUE map_type;
  typedef unsigned long size_type;
  typedef COMPARE compare;

private:
  vector<tuple<key_type, map_type> > mData;
  compare comparator;

public:
  map(){
  }
  template<class inputIter>
  map(inputIter first, inputIter last){
    for(;first != last; ++first){
      mData.push_back(*first);
    }

    std::sort(mData.begin(), mData.end());
  }
  map(const map& other){
  }
  map(map&& other){
  }

  map_type& at(key_type key){
    unsigned int idx;
    unsigned int min = 0;
    unsigned int max = mData.size();

    idx = (max - min) / 2;

    while(get<0>(mData[idx]) != key){
      if(min == max){
        throw keyNotFoundException();
      }
      if(comparator(key, get<0>(mData[idx]))){
        max = idx;
      } else {
        min = idx;
      }

      idx = (max - min) / 2;
    }
  }
  map_type& operator[](key_type key){
    try{
      return at(key);
    } catch (keyNotFoundException& ex){
      mData.push_back(make_tuple(key_type(), map_type()));
      std::sort(mData.begin(), mData.end());

      return at(key);
    }
  }

  bool empty() const{
    return mData.empty();
  }
  size_type size() const{
    return mData.size();
  }
};

#endif

