#ifndef __OBJECT_H__
#define __OBJECT_H__


namespace Jing {

class Object {
public:
  virtual Object() = 0;
  virtual bool equals(Object obj) = 0;
  virtual bool operator==(Object rhs) = 0;
  virtual int hashCode() = 0;

protected:
  virtual Object clone() = 0;
  virtual void finalize() = 0;
};

}

#endif

