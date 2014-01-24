#ifndef __LIST_H__
#define __LIST_H__

#include<Collection.hh>
#include<Iterable.hh>

namespace Jing{

template<class T>
class List:Collection<T>:Iterable<T>{
public:
  bool addAll(int index, Collection<T> c);
  T get(int index);
  int indexOf(Object o);
  int lastIndexOf(Object o);
  ListIterator<T> listIterator();
  ListIterator<T> listIterator(int index);
  T remove(int index);
  T set(int index, T element);
  List<T> subList(int fromIndex, int toIndex);
};

}

#endif

