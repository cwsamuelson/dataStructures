#ifndef __ARRAYLIST_H__
#define __ARRAYLIST_H__

#include"Collection.hh"
#include<Jing/Misc.h>

namespace Jing{

template<class T>
class ArrayList:public Collection<T>{
  typedef unsigned int index_t;
  typedef unsigned int size_t;

private:
  class listNode{
    friend class ArrayList<T>;
  private:
    T data;
    listNode *next;
    listNode *prev;

    void init();

  public:
    listNode(T t);

    bool add(T t);
    bool add(T t, index_t n);
    T remove(index_t n);
    T get(index_t n) const;
    index_t find(T t, index_t n);
    index_t backFind(T t, index_t n);
  };

  class listIterator:public Iterator<T>{
    private:
      index_t idx;
      ArrayList* theList;

    public:
      listIterator(ArrayList* thisList);
      listIterator(ArrayList* thisList, index_t n);
      bool hasNext();
      T next();
      void remove();
      void reset();
  };

  listNode *first;
  listNode *last;
  size_t count;
  listIterator *iter;

  void init();

public:
  ArrayList();
  ArrayList(Collection<T> *c);
  ArrayList(int initialCapacity);

  bool add(T t);
  bool add(T t, index_t n);
  bool addAll(Collection<T> *c);
  bool addAll(Collection<T> *c, index_t n);
  void clear();
  T clone();
  bool contains(T t);
  bool containsAll(Collection<T> *c);
  bool equals(T t);
  void ensureCapacity(int minCapacity);
  T get(index_t n) const;
  index_t indexOf(T t) const;
  index_t lastIndexOf(T t) const;
  bool isEmpty();
  Iterator<T> *iterator();
  Iterator<T> *iterator(index_t n);
  T remove();
  T remove(index_t n);
  bool remove(T t);
  bool removeAll(Collection<T> *c);
  bool retainAll(Collection<T> *c);
  void removeRange(int fromIndex, int toIndex);
  int  hashCode();
  size_t  size();
  T* toArray();
  T* toArray(T* arr);
  void trimToSize();
};

}

#include"list.cc"

#endif

