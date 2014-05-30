#ifndef __ABSTRACT_TREE_H__
#define __ABSTRACT_TREE_H__

#include<Jing/Object.hh>
#include<Jing/Collection.hh>
#include<Jing/AbstractList.hh>

namespace Jing{

class AbstractTree:public Collection{
public:
  virtual bool add(Object o1, Object o2) = 0;
  virtual bool addAll(AbstractTree *at) = 0;
  virtual bool addAll(AbstractList *alx, AbstractList *aly) = 0;
  virtual Object remove(Object o) = 0;
  virtual bool removeAll(AbstractList *al) = 0;
  virtual bool removeAll(AbstractTree *al) = 0;
  virtual void toArray(Object *o1, Object *o2) const = 0;
//  virtual Object* toArray() const = 0;
};

}

#endif

