#ifndef __COLLECTION_H__
#define __COLLECTION_H__

#include"Iterable.hh"

namespace Jing{

template<class T>
class Collection:Iterable<T>{
public:
  virtual bool add(T t) = 0;
  virtual bool addAll(Collection<T> *c) = 0;
  virtual void clear() = 0;
//  virtual bool contains(Object o) = 0;
  virtual bool containsAll(Collection<T> *c) = 0;
//  virtual bool equals(Object o) = 0;
  virtual int  hashCode() = 0;
  virtual bool isEmpty() = 0;
//  virtual bool remove(Object o) = 0;
  virtual bool removeAll(Collection<T> *c) = 0;
  virtual bool retainAll(Collection<T> *c) = 0;
  virtual Iterator<T> *iterator() = 0;
  virtual unsigned int  size() const = 0;
//  virtual Object[] toArray() = 0;
  virtual T* toArray() = 0;
};

}

#endif

