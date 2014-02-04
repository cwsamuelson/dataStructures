#ifndef __COLLECTION_H__
#define __COLLECTION_H__

#include<Jing/Iterable.hh>

namespace Jing{

template<class T>
class Collection:public Iterable<T>{
public:
  virtual void clear() = 0;
  virtual bool contains(T t) const = 0;
  virtual bool containsAll(Collection<T> *c) const = 0;
  virtual bool equals(Collection<T>* c) const = 0;
  virtual int  hashCode() const = 0;
  virtual bool isEmpty() = 0;
  virtual unsigned int  size() const = 0;
};

}

#endif

