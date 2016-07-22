#ifndef __MAP_HH__
#define __MAP_HH__

#include<algorithm>
#include<exception>
#include<functional>

#include<normal_iterator.hh>
#include<vector.hh>
#include<tuple.hh>

class keyNotFoundException : public std::exception{
public:
  virtual const char* what() const noexcept{
    return "Requested key not found!";
  }
};

template<class KEY, class VALUE, class COMPARE = std::less<KEY> >
class map{
public:
  typedef KEY key_type;
  typedef VALUE map_type;
  typedef unsigned long size_type;
  typedef COMPARE compare;
  typedef tuple<key_type, map_type> storage_type;
  typedef normal_iterator<storage_type, map> iterator;

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
    mData = other.mData;
    comparator = other.comparator;
  }
  map(map&& other){
    mData = std::forward<decltype(mData)>(other.mData);
    comparator = other.comparator;
  }
  virtual ~map(){
  }

  map_type& at(key_type key){
    if(mData.empty()){
      throw keyNotFoundException();
    }

    unsigned int idx;
    unsigned int min = 0;
    unsigned int max = mData.size() - 1;

    idx = (max + min) / 2.0;

    while(get<0>(mData[idx]) != key){
      if(min == max || idx >= mData.size()){
        throw keyNotFoundException();
      }
      if(comparator(key, get<0>(mData[idx]))){
        max = idx - 1;
      } else {
        min = idx + 1;
      }

      idx = (max + min) / 2.0;
    }
    return get<1>(mData[idx]);
  }
  map_type& operator[](const key_type& key){
    try{
      return at(key);
    } catch (keyNotFoundException& ex){
      mData.push_back(make_tuple(key, map_type()));
      normalize();

      return at(key);
    }
  }
  const map_type& operator[](const key_type& key) const{
    return (*this)[key];
  }

  template<class inputIter>
  void insert(inputIter first, inputIter last){
    for(;first != last; ++first){
      mData.push_back(*first);
    }
    normalize();
  }
  template<class ...Args>
  iterator emplace(Args ...args){
    mData.emplace_back(args...);
    normalize();
  }

  iterator begin(){
    return mData.begin();
  }
  const iterator cbegin() const{
    return begin();
  }
  iterator end(){
    return mData.end();
  }
  const iterator cend() const{
    return end();
  }

  bool empty() const{
    return mData.empty();
  }
  size_type size() const{
    return mData.size();
  }
};

#endif

