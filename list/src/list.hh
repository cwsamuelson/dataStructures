#ifndef __LIST_H__
#define __LIST_H__

#include<Jing/AbstractList.hh>
#include<Jing/Misc.hh>
#include<iostream>
using std::cout;
using std::endl;

namespace Jing{

template<class T>
class list:public AbstractList<T>{
private:
  bool sameType;

protected:
  class listNode{
    friend class list;
  private:
    T& data;
    listNode *prev;
    listNode *next;

  public:
    listNode(T& obj);
    listNode(T& obj, listNode* prev, listNode* next);

    bool add(T& obj, Jing::index_t n);
    T& remove(Jing::index_t idx);
    T& get(Jing::index_t n) const;
    bool assign(Jing::index_t idx, T& obj);
    Jing::index_t find(T& obj, Jing::index_t n);
    Jing::index_t backFind(T& obj, Jing::index_t n);
  };

  //Might neeed to make this a template, implies making iterable and iterator templates as well
  class listIterator:public Iterator<T>{
  private:
  //OPTIMIZE:Make friend to list to point directly to nodes.
  //  friend class list;
    Jing::index_t idx;
    list<T>& theList;

  public:
    listIterator(Jing::list<T>& thisList);
    listIterator(Jing::list<T>& thisList, Jing::index_t n);

    bool hasNext();
    T& next();
    void remove();
    void reset();
  };

  listNode *first;
  listNode *last;
  size_t count;
  listIterator *iter;

public:
//TODO:clear warnings
//TODO:equals method
//TODO:hashing
//TODO:classID dynamic infrastructure
//TODO:allow iterators to be used as insertion points
//TODO:Allow for multiple iterators
//TODO:remove character include
//TODO:remove iostream pieces and parts

//Constructors
  list();
  list(Collection<T>& c);
//Inserts
//  [inherited from abstractlist]
  void insert(T& obj, Jing::index_t idx);
  void insertAll(Collection<T>& c, Jing::index_t idx);
//  [inherited from collection]
  void insert(T& obj);
  void insertAll(Collection<T>& c);
//Removes
  T& remove();
//  [inherited from abstractlist]
  T& remove(Jing::index_t idx);
  void removeRange(Jing::index_t srtIdx, Jing::index_t endIdx);
//  [inherited from collection]
  void remove(T& obj);
  void removeAll(Collection<T>& c);
//Gets
//  [inherited from abstractlist]
  T& get() const;
  T& get(Jing::index_t idx) const;
//clean up with delete
  virtual AbstractList<T>& get(index_t start, index_t end) const;
//Assign
//  [inherited from abstractlist]
  T& assign(Jing::index_t idx, T& obj);
//Contains
//  [inherited from collection]
  bool contains(T& obj) const;
  bool containsAll(Collection<T>& c) const;
//Reverse gets
//  [inherited from abstractlist]
  Jing::index_t indexOf(T& obj) const;
  Jing::index_t lastIndexOf(T& obj) const;
//Equality
//  [inherited from Object]
  bool equals(Object& obj) const;
//Iterator
//  [inherited from Iterable]
  Iterator<T>& iterator() const;
//States
//  hash
//  [inherited from Object]
  int hash() const;
//  ID
//  [inherited from Object]
  int classID() const;
//  clone
//  [inherited from Object]
//memory management may be up to the user.
//clean up with delete
  Object* clone() const;
//  [inherited from abstractlist]
  Object* toArray() const;
  void toArray(Object* arr) const;
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

//Exceptions not currently needed in list
/*
class listException:public exception{
};

class listIndexOutOfBounds:public listException{
private:
  void initWithList(const Jing::list& theList);
public:
  listIndexOutOfBounds(const char * message);
  listIndexOutOfBounds(const Jing::string& message);
  listIndexOutOfBounds(const list& theList);
  listIndexOutOfBounds(const list& theList, Jing::index_t index);
  listIndexOutOfBounds(const listNode& node);

//  const string& what() const;
};
*/


}

#include"list.cc"

#endif

