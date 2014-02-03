#ifndef __COMPARATOR_H__
#define __COMPARATOR_H__

namespace Jing{

template<class T>
class Comparator{
public:
  virtual int compare(T o1, To2) = 0;
  virtual bool equals(Object obj) = 0;
};

}

#endif

