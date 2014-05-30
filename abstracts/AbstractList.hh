#ifndef __ABSTRACT_LIST_H__
#define __ABSTRACT_LIST_H__

#include<Jing/Collection.hh>

namespace Jing{

class AbstractList:public Collection{
public:
  virtual bool add(Object obj) = 0;
  virtual bool addAll(AbstractList *c) = 0;
  virtual bool remove(Object obj) = 0;
  virtual bool removeAll(AbstractList *c) = 0;
  virtual Object* toArray() = 0;
//  virtual Object[] toArray() = 0;
};

}

#endif

