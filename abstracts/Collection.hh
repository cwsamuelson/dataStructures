#ifndef __COLLECTION_H__
#define __COLLECTION_H__

#include<Jing/Iterable.hh>

namespace Jing{

class Collection:public Iterable{
public:
  virtual void clear() = 0;
  virtual bool contains(Object obj) const = 0;
  virtual bool containsAll(Collection *c) const = 0;
  virtual bool equals(Collection* c) const = 0;
  virtual int  hashCode() const = 0;
  virtual bool isEmpty() const = 0;
  virtual unsigned int  size() const = 0;
};

}

#endif

