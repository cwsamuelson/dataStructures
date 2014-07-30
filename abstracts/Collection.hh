#ifndef __COLLECTION_H__
#define __COLLECTION_H__

#include<Jing/Iterable.hh>

namespace Jing{

//unsigned long long?
typedef unsigned long size_t;

template<class T>
class Collection:public Iterable<T>{
public:
//*Alls might need to use const parameter.
//Inserts
  virtual void insert(T& obj) = 0;
  virtual void insertAll(Collection<T>& c){
    Iterator<T>& iter = c.iterator();
    while(iter.hasNext()){
      this->insert(iter.next());
    }
  }
//Removes
  virtual void remove(T& obj) = 0;
  virtual void removeAll(Collection<T>& c){
    Iterator<T>& iter = c.iterator();
    while(iter.hasNext()){
      this->remove(iter.next());
    }
  }
//Contains
  virtual bool contains(T& obj) const = 0;
  virtual bool containsAll(Collection<T>& c) const{
    Iterator<T>& iter = c.iterator();
    while(iter.hasNext()){
      this->contains(iter.next());
    }
  }
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
//  isempty
  virtual bool isEmpty() const = 0;
//  size
  virtual size_t size() const = 0;
//  clear
  virtual void clear() = 0;
};

}

#endif

