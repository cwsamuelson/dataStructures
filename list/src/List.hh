#ifndef __LIST_H__
#define __LIST_H__

#include<Jing/AbstractList.hh>
#include<Jing/Misc.hh>

namespace Jing{

template<class T>
class List:public AbstractList<T>{
protected:
  class listNode{
    friend class List;
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
    List<T>& theList;
    listNode* curNode;

  public:
    listIterator(Jing::List<T>& thisList);

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
//TODO:equals method
//TODO:allow iterators to be used as insertion points
//TODO:Allow for multiple iterators

//Constructors
  List();
  List(Collection<T>& c);
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
//TODO:equality checks should really only be against, abstract lists..
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
  void initWithList(const Jing::List& theList);
public:
  listIndexOutOfBounds(const char * message);
  listIndexOutOfBounds(const Jing::string& message);
  listIndexOutOfBounds(const List& theList);
  listIndexOutOfBounds(const List& theList, Jing::index_t index);
  listIndexOutOfBounds(const listNode& node);

//  const string& what() const;
};
*/


}

#include"List.cc"

#endif

