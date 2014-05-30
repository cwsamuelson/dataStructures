#ifndef __ARRAYLIST_H__
#define __ARRAYLIST_H__

#include<Jing/AbstractList.hh>
#include<Jing/except>
#include<Jing/Misc.hh>

namespace Jing{

class list:public AbstractList{
private:
  class listNode{
    friend class list;
  private:
    Object data;
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

  class listIterator:public Iterator{
    private:
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

  listNode *first;
  listNode *last;
  size_t count;
  listIterator *iter;

  void init();

public:
  list();
  list(AbstractList *c);
  list(int initialCapacity);

  bool add(Object obj);
  bool add(Object obj, index_t n);
  bool addAll(AbstractList *c);
  bool addAll(AbstractList *c, index_t n);
  void clear();
//  Object clone();
  bool contains(Object obj) const;
  bool containsAll(Collection *c) const;
  bool equals(Collection *c) const;
  void ensureCapacity(int minCapacity);
  Object get(index_t n) const;
  index_t indexOf(Object obj) const;
  index_t lastIndexOf(Object obj) const;
  bool isEmpty() const;
  Iterator *iterator() const;
  Object remove();
  Object remove(index_t n);
  bool remove(Object obj);
  bool removeAll(AbstractList *c);
  void removeRange(int fromIndex, int toIndex);
  int  hashCode() const;
  size_t size() const;
  Object* toArray();
  void toArray(Object* arr);
  void trimToSize();

  class listIndexOutOfBounds : public exception{
  private:
    void initWithList(const Jing::list& theList);
  public:
    listIndexOutOfBounds(const char * message);
    listIndexOutOfBounds(const string& message);
    listIndexOutOfBounds(const list& theList);
    listIndexOutOfBounds(const list& theList, int index);
  
  //  const string& what() const;
  };

};

}

#include"list.cc"

#endif

