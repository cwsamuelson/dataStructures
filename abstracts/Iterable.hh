#ifndef __ITERABLE_H__
#define __ITERABLE_H__

#include<Jing/Iterator.hh>

namespace Jing{

template<class T>
class Iterable{
public:
  virtual Iterator<T> *iterator() const = 0;
};

}

#endif

