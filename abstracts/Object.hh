#ifndef __OBJECT_H__
#define __OBJECT_H__

namespace Jing{

class Object{
public:
  virtual Object clone();
  virtual bool equals(Object obj);
  virtual int hash();
  virtual String toString();
};

}

#endif

