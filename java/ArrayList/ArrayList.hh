#ifndef __ARRAYLIST_H__
#define __ARRAYLIST_H__

#include<Iterable.hh>
#include<Collection.hh>
#include<List.hh>

namespace Jing{

template<class T>
class ArrayList:AbstractList<T>:Iterable<T>:Collection<T>:List<T>:Serializable:Cloneable:RandomAccess{
public:
  ArrayList();
  ArrayList(Collection<T> c);
  ArrayList(int initialCapacity);

  void ensureCapacity(int minCapacity);
  void trimToSize();

protected:
  void removeRange(int fromIndex, int toIndex);
};

}

#endif

