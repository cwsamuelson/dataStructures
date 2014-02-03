#ifndef __ADSTRACTLIST_H__
#define __ADSTRACTLIST_H__

#include<AbstractCollection.hh>
#include<Iterable.hh>
#include<Collection.hh>
#include<List.hh>

namespace Jing{

template<class T>
class AbstractList:AbstractCollection<T>:Iterable<T>:Collection<T>:List<T>{
public:
protected:
  AbstractList();
  virtual void removeRange(int fromIndex, int toIndex) = 0;
};

}

#endif

