#ifndef __COLLECTION_H__
#define __COLLECTION_H__

#include<Jing/Iterable.hh>

namespace Jing{

class Collection:public Iterable{
public:
//Inserts
  virtual void insert(Object& obj) = 0;
  virtual void insertAll(Collection& c) = 0;
//Removes
  virtual void remove(Object& obj) = 0;
  virtual void removeAll(Collection& c) = 0;
//Contains
  virtual bool contains(Object& obj) const = 0;
  virtual bool containsAll(Collection& c) const = 0;
//Equality
//  [inherited from Object]
//  virtual bool equals(Object& obj) const = 0;
//Iterator
//  [inherited from Iterable]
//  virtual Iterator& iterator() const = 0;
//States
//  [inherited from Object]
//  hash
//  virtual int hash() const = 0;
//  ID
//  virtual int classID() const = 0;
//  clone
//  virtual Object clone() const = 0;
//  isempty
  virtual bool isEmpty() const = 0;
//  size
  virtual int size() const = 0;
//  clear
  virtual void clear() = 0;
};

}

#endif

