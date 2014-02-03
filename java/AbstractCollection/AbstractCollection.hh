#ifndef __ABSTRACT_COLLECTION_H__
#define __ABSTRACT_COLLECTION_H__

#include<Object.hh>
#include<Iterable.hh>
#include<Collection.hh>

namespace Jing{

template<class T>
class AbstractCollection:Object:Iterable<T>:Collection<T>{
protected:
  virtual AbstractCollection() = 0;
public:
};

}

#endif

