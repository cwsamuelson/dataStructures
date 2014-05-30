#ifndef __ITERATOR_H__
#define __ITERATOR_H__

#include<Jing/Object.hh>

namespace Jing{

class Iterator{
public:
  virtual bool hasNext() = 0;
  virtual Object next() = 0;
  virtual void remove() = 0;
  virtual void reset() = 0;
};

}

#endif

