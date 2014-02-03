#ifndef __COMPARABLE_H__
#define __COMPARABLE_H__

namespace Jing{

template<class T>
class Comparable{
public:
  virtual int compareTo(T o) = 0;
};

}

#endif

