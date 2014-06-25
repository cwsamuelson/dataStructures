#ifndef __ABSTRACT_LIST_H__
#define __ABSTRACT_LIST_H__

#include<Jing/Collection.hh>

namespace Jing{

typedef unsigned int index_t;

class AbstractList:public Collection{
public:
//Inserts
  virtual void insert(Object& obj, index_t idx) = 0;
  virtual void insertAll(Collection& c, index_t idx) = 0;
//  [inherited from collection]
//  virtual void insert(Object& obj) = 0;
//  virtual void insertAll(Collection& c) = 0;
//Removes
  virtual Object& remove(index_t idx) = 0;
  virtual void removeRange(index_t srtIdx, index_t endIdx) = 0;
//  [inherited from collection]
//  virtual void remove(Object& obj) = 0;
//  virtual void removeAll(Collection& c) = 0;
//Gets
  virtual Object& get() const = 0;
  virtual Object& get(index_t idx) const = 0;
  virtual AbstractList& get(index_t start, index_t end) const = 0;
//Assign
  virtual Object& assign(index_t idx, Object& obj) = 0;
//Contains
//  [inherited from collection]
//  virtual bool contains(Object& obj) const = 0;
//  virtual bool containsAll(Collection& c) const = 0;
//Reverse gets
  virtual index_t indexOf(Object& obj) const = 0;
  virtual index_t lastIndexOf(Object& obj) const = 0;
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
//  virtual Object* clone() const = 0;
  virtual Object* toArray() const = 0;
  virtual void toArray(Object* arr) const = 0;
//  isempty
//  [inherited from collection]
//  virtual bool isEmpty() const = 0;
//  size
//  virtual int size() const = 0;
//  clear
//  virtual void clear() = 0;
};

}

#endif

