#ifndef __QUEUE_H__
#define __QUEUE_H__

#include<Jing/Collection.hh>
#include<Jing/List>
#include<Jing/Misc.hh>

namespace galaxy{

template<class T>
class Queue:public Collection<T>{
protected:
  list<T> que;

public:
//TODO:clear warnings
//TODO:equals method
//TODO:allow iterators to be used as insertion points
//TODO:Allow for multiple iterators

//Constructors
  Queue();
  Queue(Collection<T>& c);
//Inserts
  void enqueue(T& obj);
//  [inherited from collection]
  void insert(T& obj);
  void insertAll(Collection<T>& c);
//Removes
  T& dequeue();
  T& remove();
//  [inherited from collection]
  void remove(T& obj);
  void removeAll(Collection<T>& c);
//Contains
//  [inherited from collection]
  bool contains(T& obj) const;
  bool containsAll(Collection<T>& c) const;
//Reverse gets
//Equality
//  [inherited from Object]
  bool equals(Object& obj) const;
//Iterator
//  [inherited from Iterable]
  Iterator<T>& iterator() const;
//States
//  hash
//  [inherited from Object]
  unsigned long long hash() const;
//  clone
//  [inherited from Object]
//memory management may be up to the user.
//clean up with delete
  Object* clone() const;
//  isempty
//  [inherited from collection]
  bool isEmpty() const;
//  size
//  [inherited from collection]
  size_t size() const;
//  clear
//  [inherited from collection]
  void clear();
};

#include"Queue.cc"

}

#endif

