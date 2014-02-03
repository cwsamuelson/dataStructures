#ifndef __ITERABLE_H__
#define __ITERABLE_H__

#include<Iterator.hh>

namespace Jing{

template<class T>
class Iterable{
public:
  virtual Iterator<T> iterator() = 0;
};

}

#endif

