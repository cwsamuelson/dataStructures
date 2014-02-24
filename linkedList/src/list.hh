#ifndef __ARRAYLIST_H__
#define __ARRAYLIST_H__

#include<Jing/AbstractList.hh>
#include<Jing/except>
#include<Jing/Misc.hh>

namespace Jing{

class listIndexOutOfBounds : public exception{
public:
  listIndexOutOfBounds(const char * message);
  listIndexOutOfBounds(const string& message);

  const string& what() const;
};

template<class T>
class ArrayList:public AbstractList<T>{
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
  ArrayList(AbstractList<T> *c);
  ArrayList(int initialCapacity);

  bool add(T t);
  bool add(T t, index_t n);
  bool addAll(AbstractList<T> *c);
  bool addAll(AbstractList<T> *c, index_t n);
  void clear();
//  T clone();
  bool contains(T t) const;
  bool containsAll(Collection<T> *c) const;
  bool equals(Collection<T> *c) const;
  void ensureCapacity(int minCapacity);
  T get(index_t n) const;
  index_t indexOf(T t) const;
  index_t lastIndexOf(T t) const;
  bool isEmpty() const;
  Iterator<T> *iterator() const;
  T remove();
  T remove(index_t n);
  bool remove(T t);
  bool removeAll(AbstractList<T> *c);
  void removeRange(int fromIndex, int toIndex);
  int  hashCode() const;
  size_t size() const;
  T* toArray();
  void toArray(T* arr);
  void trimToSize();
};

}

#include"list.cc"

#endif

