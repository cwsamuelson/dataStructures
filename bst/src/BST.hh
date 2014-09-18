#ifndef __BST_H__
#define __BST_H__

#include<Jing/Comparable.hh>
#include<Jing/AbstractTree.hh>
#include<Jing/AbstractList.hh>
#include<Jing/Misc.hh>

namespace Jing{

template<class X, class Y>
class BST:public AbstractTree<X, Y>{
private:
  class treeNode{
    friend class BST<X,Y>;
  private:
    X& key;
    Y& value;
    treeNode *parent;
    treeNode *left;
    treeNode *right;

    void init();

  public:
    treeNode(X& x, Y& y);
    treeNode(X& x, Y& y, treeNode* parent);

    bool add(X& x, Y& y);
    Y& remove(X& x);
    Y& get(X& x) const;
    X& find(Y& y) const;
  };

  class treeIterator:public Iterator<Y>{
  private:
    X& key;
    BST* theTree;
  public:
    treeIterator(BST *thisList);

    bool hasNext();
    Y& next();
    void remove();
    void reset();
  };

  treeNode *root;
  size_t count;
  treeIterator *iter;

  void init();

public:
//Constructors
  BST();
  BST(AbstractTree<X, Y>& at);
  BST(AbstractList<X>& alx, AbstractList<Y>& aly);
//Inserts
//  [inherited from collection]
  void insert(Y& obj);
  void insertAll(Collection<Y>& c);
//  [inherited from abstractTree]
  bool insert(X& x, Y& y);
  bool insertAll(AbstractTree<X,Y>& at);
  bool insertAll(AbstractList<X>& alx, AbstractList<Y>& aly);
//Gets
  Y& get(X& x) const;
  X& getKey(Y& y) const;
//Removes
//  [inherited from collection]
//Remove by key
  void removeAll(Collection<X>& c);
//  [inherited from abstractTree]
  Y& remove(X& x);
  Y& removeByKey(X& x);
  X& removeByData(Y& y);
  bool removeAll(AbstractList<X>& al);
  bool removeAllByKey(AbstractList<X>& al);
  bool removeAllByData(AbstractList<Y>& al);
//Contains
  bool containsKey(X& x) const;
  bool containsValue(Y& y) const;
//  [inherited from colleciton]
  bool contains(Y& obj) const;
  bool containsAll(Collection<Y>& c) const;
//Equality
//  [inherited from object]
  bool equals(BST& obj) const;
//States
//  hash
//  [inherited from object]
  unsigned long long hash() const;
//  clone
  Object* clone() const;
//  empty
  bool isEmpty() const;
//  size
  size_t size() const;
// clear
  void clear();
//  iterator
//  [inherited from iterable]
  Iterator<Y>& iterator() const;





};

}

#include<Jing/BST.cc>

#endif

