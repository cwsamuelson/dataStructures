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
  typedef tuple<key_type, map_type> storage_type;

private:
  vector<storage_type> mData;
  compare comparator;

  void normalize(){
    std::sort(mData.begin(), mData.end(),
      [=](const storage_type& x, const storage_type& y)->bool{
        return comparator(get<0>(x), get<0>(y));
      }
    );
  }

public:
  map(){
  }
  template<class inputIter>
  map(inputIter first, inputIter last):
    mData(first, last){
    normalize();
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
  map_type& operator[](const key_type& key){
    try{
      return at(key);
    } catch (keyNotFoundException& ex){
      mData.push_back(make_tuple(key_type(), map_type()));
      normalize();

      return at(key);
    }
  }
  const map_type& operator[](const key_type& key) const{
    try{
      return at(key);
    } catch (keyNotFoundException& ex){
      mData.push_back(make_tuple(key_type(), map_type()));
      normalize();

      return at(key);
    }
  }

  template<class inputIter>
  void insert(inputIter first, inputIter last){
    for(;first != last; ++first){
      mData.push_back(*first);
    }
    normalize();
  }
  bool empty() const{
    return mData.empty();
  }
  size_type size() const{
    return mData.size();
  }
};

#endif

