#ifndef __ABSTRACT_LIST_H__
#define __ABSTRACT_LIST_H__

#include<Jing/Collection.hh>

namespace Jing{

typedef unsigned long long index_t;

template<class T>
class AbstractList:public Collection<T>{
public:
//Inserts
  virtual void insert(T& obj, index_t idx) = 0;
  virtual void insertAll(Collection<T>& c, index_t idx) = 0;
//  [inherited from collection]
//  virtual void insert(T& obj) = 0;
//  virtual void insertAll(Collection<T>& c) = 0;
//Removes
  virtual T& remove(index_t idx) = 0;
  virtual void removeRange(index_t srtIdx, index_t endIdx) = 0;
//  [inherited from collection]
//  virtual void remove(T& obj) = 0;
//  virtual void removeAll(Collection<T>& c) = 0;
//Gets
  virtual T& get() const = 0;
  virtual T& get(index_t idx) const = 0;
  virtual AbstractList& get(index_t start, index_t end) const = 0;
//Assign
  virtual T& assign(index_t idx, T& obj) = 0;
//Contains
//  [inherited from collection]
//  virtual bool contains(T& obj) const = 0;
//  virtual bool containsAll(Collection<T>& c) const = 0;
//Reverse gets
  virtual index_t indexOf(T& obj) const = 0;
  virtual index_t lastIndexOf(T& obj) const = 0;
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

