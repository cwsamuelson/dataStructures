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

  public:
    treeNode(X& x, Y& y);
    treeNode(X& x, Y& y, treeNode* parent);

    bool add(X& x, Y& y);
    Y& remove(X& x);
    Y& get(X& x) const;
    X& find(Y& y) const;
  };
/*
  class treeIterator:public Iterator<Y>{
  private:
    X& key;
    BST<X, Y>* theTree;
  public:
    treeIterator(BST<X, Y> *thisList);

    bool hasNext();
    Y& next();
    void remove();
    void reset();
  };
*/

  treeNode *root;
  size_t count;
//  treeIterator *iter;

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
  void insert(X& x, Y& y);
  void insertAll(AbstractTree<X,Y>& at);
  void insertAll(AbstractList<X>& alx, AbstractList<Y>& aly);
//Gets
  X& get(Y& y) const;
  X& getByKey(Y& y) const;
  Y& getByData(X& x) const;
//Removes
//  [inherited from collection]
//Remove by key
  void remove(Y& y);
  void removeAll(Collection<X>& c);
//  [inherited from abstractTree]
  void remove(X& x);
  void removeByKey(X& x);
  void removeByData(Y& y);
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
  bool equals(BST<X, Y>& obj) const;
//  [inherited from object]
  bool is_equal(const Object& obj)const;
  bool equals(Object& obj) const;
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
  Iterator<Y>* iterator() const;





};

}

#include<Jing/BST.cc>

#endif

