#ifndef __RANGE_HH__
#define __RANGE_HH__

#include<iostream>

template<class>
class range;

template<class CONTAINER>
class range_iterator{
public:
  typedef CONTAINER container;
  typedef typename container::value_type value_type;
  typedef typename container::value_type& reference;
  typedef typename container::value_type* pointer;
  typedef const value_type const_value;
  typedef typename container::iterator iterator;

private:
  const range<container>* mRange;
  iterator mIterator;

public:
  range_iterator(const range<container>* rang, iterator iter):
    mRange(rang),
    mIterator(iter){
  }
  range_iterator(const range_iterator& iter):
    mRange(iter.mRange),
    mIterator(iter.mIterator){
  }

  bool operator==(const range_iterator& other) const{
    return (mRange == other.mRange) && (mIterator == other.mIterator);
  }
  bool operator==(const iterator& other) const{
    return mIterator == other;
  }
  bool operator!=(const range_iterator& other) const{
    return !((*this) == other);
  }
  bool operator!=(const iterator& other) const{
    return !(mIterator == other);
  }

  value_type operator*() const{
    return mRange->mModifier(*mIterator);
  }
  pointer operator->() const{
    return mIterator.operator->();
  }
  
  range_iterator& operator++(){
    while(!mRange->mFilter(*++mIterator)){
      ;
    }
    return *this;
  }
  range_iterator operator++(int){
    range_iterator ret(*this);
    ++(*this);
    return ret;
  }
  
  range_iterator& operator--(){
    while(!mRange->mFilter(*--mIterator)){
      ;
    }
    return *this;
  }
  range_iterator operator--(int){
    range_iterator ret(*this);
    --(*this);
    return ret;
  }
};

template<class CONTAINER>
class range{
public:
  typedef CONTAINER container;
  typedef typename container::value_type value_type;
  typedef typename container::pointer pointer;
  typedef typename container::reference reference;
  typedef typename container::iterator contIter;
  typedef std::function<bool(const reference)> filter;
  typedef std::function<value_type(const reference)> modifier;
  typedef range_iterator<container> iterator;

private:
  contIter mBegin;
  contIter mEnd;
  filter mFilter;
  modifier mModifier;

  friend iterator;

public:
  range(contIter begin, contIter end,
        filter filFN = [](const reference){ return true; },
        modifier modFN = [](const reference t){ return t; }):
    mBegin(begin),
    mEnd(end),
    mFilter(filFN),
    mModifier(modFN){
  }
  range(container& cont, 
        filter filFN = [](const reference){ return true; },
        modifier modFN = [](const reference t){ return t; }):
    range(cont.begin(), cont.end(), filFN, modFN){
  }
  
  iterator begin(){
    contIter iter(mBegin);
    while(!mFilter(*iter)){
      ++iter;
    }
    return iterator(this, iter);
  }
  iterator end(){
    contIter iter(mEnd);
    while(!mFilter(*iter)){
      --iter;
    }
    return iterator(this, iter);
  }
};

#endif

