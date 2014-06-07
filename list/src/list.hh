#ifndef __ARRAYLIST_H__
#define __ARRAYLIST_H__

#include<Jing/AbstractList.hh>
#include<Jing/except>
#include<Jing/Misc.hh>

namespace Jing{

class list:public AbstractList{
private:
  void init();
  bool sameType;
  int storedID;

protected:
  class listNode{
    friend class list;
  private:
    Object& data;
    listNode *next;
    listNode *prev;

    void init();

  public:
    listNode(Object obj);

    bool add(Object obj);
    bool add(Object obj, index_t n);
    Object remove(index_t n);
    Object get(index_t n) const;
    index_t find(Object obj, index_t n);
    index_t backFind(Object obj, index_t n);
  };

  listNode *first;
  listNode *last;
  size_t count;
  listIterator *iter;

public:
//Allow dynamic additions?
//  using constructor option objects or something
//  'emplace'
//use iterators as optional insertion points

//Constructors
  list();
  list(Collection& c);
//Inserts
//  [inherited from abstractlist]
  void insert(Object& obj, index_t idx);
  void insertAll(Collection& c, index_t idx);
//  [inherited from collection]
  void insert(Object& obj);
  void insertAll(Collection& c);
//Removes
  Object& remove();
//  [inherited from abstractlist]
  Object& remove(index_t idx);
  void removeAll(Collection& c, index_t idx);
  void removeRange(index_t srtIdx, index_t endIdx);
//  [inherited from collection]
  void remove(Object& obj);
  void removeAll(Collection& c);
//Gets
//  [inherited from abstractlist]
  Object& get(index_t idx) const;
//Assign
//  [inherited from abstractlist]
  void assign(index_t idx, Object& obj);
//Contains
//  [inherited from collection]
  bool contains(Object& obj) const;
  bool containsAll(Collection& c) const;
//Reverse gets
//  [inherited from abstractlist]
  index_t indexOf(Object& obj) const;
  index_t lastIndexOf(Object& obj) const;
//Equality
//  [inherited from Object]
  bool equals(Object& obj) const;
//Iterator
//  [inherited from Iterable]
  Iterator& iterator() const;
//States
//  hash
//  [inherited from Object]
  int hash() const;
//  ID
//  [inherited from Object]
  int classID() const;
//  clone
//  [inherited from Object]
  Object clone() const;
//  [inherited from abstractlist]
  Object* toArray() const;
  void toArray(Object* arr);
//  isempty
//  [inherited from collection]
  bool isEmpty() const;
//  size
//  [inherited from collection]
  int size() const;
//  clear
//  [inherited from collection]
  void clear();
};

class listIndexOutOfBounds:public exception{
private:
  void initWithList(const Jing::list& theList);
public:
  listIndexOutOfBounds(const char * message);
  listIndexOutOfBounds(const string& message);
  listIndexOutOfBounds(const list& theList);
  listIndexOutOfBounds(const list& theList, int index);

//  const string& what() const;
};

class listIterator:public Iterator{
private:
//must be friend to optimize?
//  friend class list;
  index_t idx;
  list* theList;

public:
  listIterator(list* thisList);
  listIterator(list* thisList, index_t n);

  bool hasNext();
  Object next();
  void remove();
  void reset();
};

}

//#include"list.cc"

#endif

