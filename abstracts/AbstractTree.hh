#ifndef __ABSTRACT_TREE_H__
#define __ABSTRACT_TREE_H__

#include<Jing/Collection.hh>

namespace Jing{

template<class X, class Y>
class AbstractTree:public Collection<X>{
public:
  virtual bool add(X x, Y y) = 0;
  virtual bool addAll(AbstractTree<X, Y> *at) = 0;
  virtual bool addAll(AbstractList<X> *alx, AbstractList<Y> *aly) = 0;
  virtual bool removeKey(X x) = 0;
  virtual bool removeAll(AbstractList<X> *al) = 0;
  virtual bool removeAll(AbstractTree<X, Y> *al) = 0;
  virtual void toArray(X *x, Y *y) const = 0;
//  virtual T* toArray() const = 0;
};

}

#endif

