#ifndef __ITERABLE_H__
#define __ITERABLE_H__

#include<Jing/Iterator.hh>

namespace Jing{

class Iterable{
public:
  virtual Iterator *iterator() const = 0;
};

}

#endif

