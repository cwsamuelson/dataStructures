#ifndef __NORMAL_ITERATOR_HH__
#define __NORMAL_ITERATOR_HH__

// normal in the sense of 'normalized'
template<class TYPE, class CONTAINER>
class normal_iterator{
public:
  typedef CONTAINER container;
  typedef TYPE value_type;
  typedef value_type* pointer;
  typedef value_type& reference;

private:
  pointer mCurrent;

public:
  normal_iterator(pointer ptr):
    mCurrent(ptr){
  }
  normal_iterator(const normal_iterator& iter):
    mCurrent(iter.mCurrent){
  }

  bool operator==(const normal_iterator& iter) const{
    return mCurrent == iter.mCurrent;
  }
  bool operator!=(const normal_iterator& iter) const{
    return !((*this) == iter);
  }

  reference operator*() const{
    return *mCurrent;
  }
  pointer operator->() const{
    return mCurrent;
  }
  
  normal_iterator& operator++(){
    ++mCurrent;
    return *this;
  }
  normal_iterator  operator++(int){
    return normal_iterator(mCurrent++);
  }
  
  normal_iterator& operator--(){
    --mCurrent;
    return *this;
  }
  normal_iterator  operator--(int){
    return normal_iterator(mCurrent--);
  }
};

#endif

