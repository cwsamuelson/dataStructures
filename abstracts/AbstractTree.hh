#ifndef __ABSTRACT_TREE_H__
#define __ABSTRACT_TREE_H__

#include<Jing/Collection.hh>
#include<Jing/AbstractList.hh>

namespace Jing{

//class X should be restrited to be comparable using can_copy in misc.hh
template<class X, class Y>
class AbstractTree:public Collection<Y>{
public:
  virtual void insert(X& x, Y& y) = 0;
  virtual void insertAll(AbstractTree<X, Y>& at) = 0;
  virtual void insertAll(AbstractList<X>& alx, AbstractList<Y>& aly) = 0;
  virtual void remove(X& x) = 0;
  virtual void removeByKey(X& x) = 0;
  virtual void removeByData(Y& y) = 0;
  virtual bool removeAll(AbstractList<X>& al) = 0;
  virtual bool removeAllByKey(AbstractList<X>& al) = 0;
  virtual bool removeAllByData(AbstractList<Y>& al) = 0;
  virtual X& get(Y& y) const = 0;
  virtual X& getByKey(Y& y) const = 0;
  virtual Y& getByData(X& x) const = 0;
//  virtual void toArray(X& x, Y& y) const = 0;
//  virtual Object* toArray() const = 0;
};

}

#endif

