#ifndef __ITERABLE_H__
#define __ITERABLE_H__

#include<Jing/Iterator.hh>
#include<Jing/Object.hh>

namespace Jing{

template<class T>
class Iterable:public Object{
public:
//Equality
//  [inherited from Object]
  bool equals(Object& obj) const;
//States
//  [inherited from Object]
//  hash
  virtual unsigned long long hash() const = 0;
//  clone
  virtual Object* clone() const = 0;
//Iterator
  virtual Iterator<T>* iterator() = 0;
};

}

#endif

