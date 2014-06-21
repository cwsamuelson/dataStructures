#ifndef __OBJECT_H__
#define __OBJECT_H__

namespace Jing{

class Object{
protected:
public:
//Equality
  virtual bool equals(Object& obj) const = 0;
//State
//  hash
  virtual int hash() const = 0;
//  ID
  virtual int classID() const = 0;
//  clone
//memory management may be up to the user.
//clean up with delete
  virtual Object* clone() const = 0;
};

}

#endif
