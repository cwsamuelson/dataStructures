#ifndef __ABSTRACT_LIST_H__
#define __ABSTRACT_LIST_H__

#include<Jing/Collection.hh>

namespace Jing{

template<class T>
class AbstractList:public Collection<T>{
public:
  virtual bool add(T t) = 0;
  virtual bool addAll(AbstractList<T> *c) = 0;
  virtual bool remove(T t) = 0;
  virtual bool removeAll(AbstractList<T> *c) = 0;
  virtual T* toArray() = 0;
//  virtual Object[] toArray() = 0;
};

}

#endif

