#ifndef __BST_H__
#define __BST_H__

#include<Jing/AbstractTree.hh>
#include<Jing/AbstractList.hh>
#include<Jing/Misc.h>

namespace Jing{

template<class X, class Y>
class bst:public AbstractTree<X, Y>{
private:
  typedef unsigned int size_t;

  class treeNode{
    friend class bst<X,Y>;
  private:
    X key;
    Y value;
    treeNode *parent;
    treeNode *left;
    treeNode *right;

    void init();

  public:
    treeNode(X x, Y y);

    bool add(X x, Y y);
    Y remove(X x);
    Y get(X x) const;
    X find(Y y) const;
  };

  class treeIterator:public Iterator<Y>{
  private:
    X key;
    bst* theTree;
  public:
    treeIterator(bst *thisList);

    bool hasNext();
    Y next();
    void remove();
    void reset();
  };

  treeNode *root;
  size_t count;
  treeIterator *iter;

  void init();

public:
  bst();
  bst(AbstractTree<X, Y> *at);
//add similar with 2 lists?
//  bst(Collection<X> *cx, Collection<Y> *cy);
  bst(AbstractList<X> *alx, AbstractList<Y> *aly);

  bool add(X x, Y y);
  bool addAll(AbstractTree<X, Y> *at);
  bool addAll(AbstractList<X> *alx, AbstractList<Y> *aly);
  Y    remove(X x);
  bool removeAll(AbstractList<X> *al);
//uh? maybe?
  bool removeAll(AbstractTree<X, Y> *at);
  Y get(X x) const;
  X getKey(Y y) const;
  void clear();
  bool contains(Y y) const;
  bool containsKey(X x) const;
  bool containsValue(Y y) const;
  bool containsAll(Collection<Y> *cy) const;
  bool isEmpty() const;
  bool equals(AbstractTree<X, Y> *at) const;
  bool equals(Collection<Y> *at) const;
  int  hashCode() const;
  void toArray(X *x, Y *y) const;
  Iterator<Y> *iterator() const;
  size_t size() const;
};

}

#include<Jing/bst.cc>

#endif

