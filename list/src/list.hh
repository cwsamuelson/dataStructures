#ifndef __ARRAYLIST_H__
#define __ARRAYLIST_H__

#include<Jing/AbstractList.hh>
#include<Jing/except>
#include<Jing/Misc.hh>

namespace Jing{

template<class T>
class list:public AbstractList<T>{
private:
  class listNode{
    friend class list<T>;
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
      list* theList;

    public:
      listIterator(list* thisList);
      listIterator(list* thisList, index_t n);
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
  list();
  list(AbstractList<T> *c);
  list(int initialCapacity);

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

  class listIndexOutOfBounds : public exception{
  private:
    void initWithList(const Jing::list<T>& theList);
  public:
    listIndexOutOfBounds(const char * message);
    listIndexOutOfBounds(const string& message);
    listIndexOutOfBounds(const list<T>& theList);
    listIndexOutOfBounds(const list<T>& theList, int index);
  
  //  const string& what() const;
  };

};

}

#include"list.cc"

#endif

